
#include "jesturepipe/graphs/jesturepipe/jesturepipe.h"

#include "jesturepipe/graphs/jesturepipe/jesturepipe_binary_graph.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {
absl::Status jesturepipe_graph(mediapipe::CalculatorGraph* graph,
                               std::string palm_model_full_path,
                               std::string palm_model_lite_path,
                               std::string landmark_model_full_path,
                               std::string landmark_model_lite_path) {
    mediapipe::CalculatorGraphConfig config;

    RET_CHECK(config.ParseFromString(JESTUREPIPE_CONFIG_CONTENTS));

    const std::map<std::string, mediapipe::Packet> side_packets = {
        {"palm_model_full_path",
         mediapipe::MakePacket<std::string>(palm_model_full_path)},
        {"palm_model_lite_path",
         mediapipe::MakePacket<std::string>(palm_model_lite_path)},
        {"landmark_model_full_path",
         mediapipe::MakePacket<std::string>(landmark_model_full_path)},
        {"landmark_model_lite_path",
         mediapipe::MakePacket<std::string>(landmark_model_lite_path)},
        {"is_recording_init", mediapipe::MakePacket<bool>(false)},
    };

    MP_RETURN_IF_ERROR(graph->Initialize(config, side_packets));

    return absl::OkStatus();
}
}  // namespace jesturepipe