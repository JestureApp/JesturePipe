#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_video_inc.h"
#include "mediapipe/framework/tool/status_util.h"

const char VideoStream[] = "VIDEO";

// TODO: docs
class CameraCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Outputs().Tag(VideoStream).Set<mediapipe::ImageFrame>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        capture.open(2);

        if (!capture.isOpened()) {
            return absl::InternalError("Failed to open camera");
        }

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        capture >> camera_frame_raw;

        if (camera_frame_raw.empty()) {
            return absl::OkStatus();
        }

        cv::cvtColor(camera_frame_raw, camera_frame, cv::COLOR_BGR2RGB);
        cv::flip(camera_frame, camera_frame, /*flipcode=HORIZONTAL*/ 1);

        auto output_frame = absl::make_unique<mediapipe::ImageFrame>(
            mediapipe::ImageFormat::SRGB, camera_frame.cols, camera_frame.rows,
            mediapipe::ImageFrame::kDefaultAlignmentBoundary);

        cv::Mat output_frame_mat =
            mediapipe::formats::MatView(output_frame.get());

        camera_frame.copyTo(output_frame_mat);

        size_t frame_timestamp =
            (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;

        cc->Outputs()
            .Tag(VideoStream)
            .Add(output_frame.release(), mediapipe::Timestamp(frame_timestamp));

        return absl::OkStatus();
    }

    absl::Status Close(mediapipe::CalculatorContext* cc) override {
        capture.release();

        return absl::OkStatus();
    }

   private:
    cv::VideoCapture capture;
    cv::Mat camera_frame_raw;
    cv::Mat camera_frame;
};

REGISTER_CALCULATOR(CameraCalculator);