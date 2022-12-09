#include "absl/status/status.h"
#include "jesturepipe/graphs/jesturepipe/jesturepipe.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"

constexpr char kOutputStream[] = "annotated_frame";
constexpr char kWindowName[] = "MediaPipe";

absl::Status RunGraph() {
    mediapipe::CalculatorGraph graph;
    MP_RETURN_IF_ERROR(jesturepipe::jesturepipe_graph(&graph));

    cv::namedWindow(kWindowName, 1);

    ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller poller,
                     graph.AddOutputStreamPoller(kOutputStream));

    MP_RETURN_IF_ERROR(graph.StartRun({}));

    while (true) {
        mediapipe::Packet packet;

        if (!poller.Next(&packet)) break;
        auto& output_frame = packet.Get<mediapipe::ImageFrame>();

        cv::Mat output_frame_mat = mediapipe::formats::MatView(&output_frame);
        cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);

        cv::imshow(kWindowName, output_frame_mat);
        const int pressed_key = cv::waitKey(5);

        if (pressed_key >= 0 && pressed_key != 255) break;
    }

    MP_RETURN_IF_ERROR(graph.CloseAllPacketSources());

    return graph.WaitUntilDone();
}

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    absl::Status status = RunGraph();

    if (!status.ok()) {
        LOG(ERROR) << status.message();
        return 1;
    }

    return 0;
}
