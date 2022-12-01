
// #include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "jesturepipe/graphs/hands/hands_demo.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "mediapipe/framework/port/opencv_video_inc.h"
#include "mediapipe/framework/port/status.h"

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "output_video";
constexpr char kWindowName[] = "MediaPipe";

absl::Status RunGraph(const std::string& arg0) {
    mediapipe::CalculatorGraph graph;
    MP_RETURN_IF_ERROR(
        jesturepipe::hand_tracking_desktop_live_graph(arg0, &graph));

    cv::VideoCapture capture;
    capture.open(0);

    RET_CHECK(capture.isOpened());

    cv::namedWindow(kWindowName, 1);

    ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller poller,
                     graph.AddOutputStreamPoller(kOutputStream));

    MP_RETURN_IF_ERROR(graph.StartRun({}));

    while (true) {
        cv::Mat camera_frame_raw;
        capture >> camera_frame_raw;

        if (camera_frame_raw.empty()) continue;

        cv::Mat camera_frame;
        cv::cvtColor(camera_frame_raw, camera_frame, cv::COLOR_BGR2RGB);
        cv::flip(camera_frame, camera_frame, /*flipcode=HORIZONTAL*/ 1);

        auto input_frame = absl::make_unique<mediapipe::ImageFrame>(
            mediapipe::ImageFormat::SRGB, camera_frame.cols, camera_frame.rows,
            mediapipe::ImageFrame::kDefaultAlignmentBoundary);

        cv::Mat input_frame_mat =
            mediapipe::formats::MatView(input_frame.get());
        camera_frame.copyTo(input_frame_mat);

        size_t frame_timestamp =
            (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;

        MP_RETURN_IF_ERROR(graph.AddPacketToInputStream(
            kInputStream, mediapipe::Adopt(input_frame.release())
                              .At(mediapipe::Timestamp(frame_timestamp))));

        mediapipe::Packet packet;
        if (!poller.Next(&packet)) break;
        auto& output_frame = packet.Get<mediapipe::ImageFrame>();

        cv::Mat output_frame_mat = mediapipe::formats::MatView(&output_frame);
        cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);

        cv::imshow(kWindowName, output_frame_mat);
        const int pressed_key = cv::waitKey(5);

        if (pressed_key >= 0 && pressed_key != 255) break;
    }

    MP_RETURN_IF_ERROR(graph.CloseInputStream(kInputStream));

    return graph.WaitUntilDone();
}

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    absl::Status status = RunGraph(argv[0]);

    if (!status.ok()) {
        LOG(ERROR) << status.message();
        return 1;
    }

    return 0;
}