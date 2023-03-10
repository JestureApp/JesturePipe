#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_video_inc.h"
#include "mediapipe/framework/tool/status_util.h"

namespace jesturepipe {

namespace api2 = mediapipe::api2;

// Example:
// node {
//     calculator: "CameraCalculator"
//     input_side_packet: "CAMERA_INDEX:camera_index"
//     output_stream: "FRAME:frame"
// }
class CameraCalculator : public api2::Node {
   public:
    static constexpr api2::SideInput<int> kCameraIndex{"CAMERA_INDEX"};

    static constexpr api2::Output<mediapipe::ImageFrame> kFrame{"FRAME"};

    MEDIAPIPE_NODE_CONTRACT(kCameraIndex, kFrame)

    absl::Status Open(mediapipe::CalculatorContext *cc) override {
        int index = *kCameraIndex(cc);

        if (!camera.open(index)) {
            return absl::InternalError("Failed to open camera with index " +
                                       std::to_string(index));
        }

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        if (!camera.read(camera_frame_raw)) {
            return absl::OkStatus();
        }

        cv::cvtColor(camera_frame_raw, camera_frame, cv::COLOR_BGR2RGB);
        cv::flip(camera_frame, camera_frame, 1);

        auto output_frame = absl::make_unique<mediapipe::ImageFrame>(
            mediapipe::ImageFormat::SRGB, camera_frame.cols, camera_frame.rows,
            mediapipe::ImageFrame::kDefaultAlignmentBoundary);

        auto output_frame_mat = mediapipe::formats::MatView(output_frame.get());

        camera_frame.copyTo(output_frame_mat);

        size_t frame_timestamp =
            (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;

        kFrame(cc).Send(std::move(output_frame),
                        mediapipe::Timestamp(frame_timestamp));

        return absl::OkStatus();
    }

    absl::Status Close(mediapipe::CalculatorContext *cc) override {
        camera.release();

        return absl::OkStatus();
    }

   private:
    cv::VideoCapture camera;
    cv::Mat camera_frame_raw;
    cv::Mat camera_frame;
};

MEDIAPIPE_REGISTER_NODE(CameraCalculator);

}  // namespace jesturepipe