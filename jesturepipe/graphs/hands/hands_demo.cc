#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/status.h"
#include "jesturepipe/graphs/hands/hands_demo_binary_graph.h"
#include "tools/cpp/runfiles/runfiles.h"

namespace jesturepipe {
using bazel::tools::cpp::runfiles::Runfiles;

absl::Status hand_tracking_desktop_live_graph(
    const std::string& arg0, mediapipe::CalculatorGraph* graph) {
    std::string error;
    std::unique_ptr<Runfiles> runfiles(Runfiles::Create(arg0, &error));

    if (runfiles == nullptr) {
        return absl::NotFoundError(error);
    }

    std::string palm_model_path = runfiles->Rlocation("mediapipe/mediapipe/modules/palm_detection/palm_detection_full.tflite");
    std::string hand_model_path = runfiles->Rlocation("mediapipe/mediapipe/modules/hand_landmark/hand_landmark_full.tflite");

    mediapipe::CalculatorGraphConfig config;

    RET_CHECK(config.ParseFromArray(HANDS_DEMO_CONFIG_CONTENTS.c_str(), HANDS_DEMO_CONFIG_CONTENTS.size()));


    const std::map<std::string, mediapipe::Packet> side_packets{
        {"palm_model_path", mediapipe::MakePacket<std::string>(palm_model_path).At(mediapipe::Timestamp(0))},
        {"landmark_model_path", mediapipe::MakePacket<std::string>(hand_model_path).At(mediapipe::Timestamp(0))},
    };
    MP_RETURN_IF_ERROR(graph->Initialize(config, side_packets));

    return absl::OkStatus();
}

}  // namespace jesturepipe