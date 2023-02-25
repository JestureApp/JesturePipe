#include "absl/status/status.h"
#include "jesturepipe/graphs/jesturepipe/jesturepipe.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "tools/cpp/runfiles/runfiles.h"

constexpr char kOutputStream[] = "annotated_frame";
constexpr char kWindowName[] = "MediaPipe";
const std::string palm_model_lite_rel_path =
    "mediapipe/mediapipe/modules/palm_detection/palm_detection_lite.tflite";
const std::string palm_model_full_rel_path =
    "mediapipe/mediapipe/modules/palm_detection/palm_detection_full.tflite";
const std::string landmark_model_lite_rel_path =
    "mediapipe/mediapipe/modules/hand_landmark/hand_landmark_lite.tflite";
const std::string landmark_model_full_rel_path =
    "mediapipe/mediapipe/modules/hand_landmark/hand_landmark_full.tflite";

using bazel::tools::cpp::runfiles::Runfiles;

absl::Status RunGraph(const std::string& arg0) {
    std::string error;
    std::unique_ptr<Runfiles> runfiles(Runfiles::Create(arg0, &error));

    if (runfiles == nullptr) {
        return absl::NotFoundError(error);
    }

    std::string palm_model_full_path =
        runfiles->Rlocation(palm_model_full_rel_path);
    std::string palm_model_lite_path =
        runfiles->Rlocation(palm_model_lite_rel_path);
    std::string landmark_model_full_path =
        runfiles->Rlocation(landmark_model_full_rel_path);
    std::string landmark_model_lite_path =
        runfiles->Rlocation(landmark_model_lite_rel_path);

    mediapipe::CalculatorGraph graph;

    MP_RETURN_IF_ERROR(jesturepipe::jesturepipe_graph(
        graph, palm_model_full_path, palm_model_lite_path,
        landmark_model_full_path, landmark_model_lite_path));

    cv::namedWindow(kWindowName, 1);

    ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller poller,
                     graph.AddOutputStreamPoller(kOutputStream));

    const std::map<std::string, mediapipe::Packet> side_packets{
        // {"palm_model_path",
        // mediapipe::MakePacket<std::string>(palm_model_path)
        //                         .At(mediapipe::Timestamp(0))},
        // {"landmark_model_path",
        //  mediapipe::MakePacket<std::string>(hand_model_path)
        //      .At(mediapipe::Timestamp(0))},
        {"camera_index",
         mediapipe::MakePacket<int>(0).At(mediapipe::Timestamp(0))},
        {"mode", mediapipe::MakePacket<int>(1).At(mediapipe::Timestamp(0))},
        {"num_hands",
         mediapipe::MakePacket<int>(2).At(mediapipe::Timestamp(0))}};

    MP_RETURN_IF_ERROR(graph.StartRun(side_packets));

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
    absl::Status status = RunGraph(argv[0]);

    if (!status.ok()) {
        LOG(ERROR) << status.message();
        return 1;
    }

    return 0;
}
