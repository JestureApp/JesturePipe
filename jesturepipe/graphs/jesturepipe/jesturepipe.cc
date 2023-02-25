
#include "jesturepipe/graphs/jesturepipe/jesturepipe.h"

#include "jesturepipe/graphs/jesturepipe/jesturepipe_binary_graph.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {
absl::Status jesturepipe_graph(mediapipe::CalculatorGraph* graph,
                               std::string palm_model_lite_path,
                               std::string palm_model_path,
                               std::string hand_model_lite_path,
                               std::string hand_model_path) {
    mediapipe::CalculatorGraphConfig config;

    RET_CHECK(config.ParseFromArray(JESTUREPIPE_CONFIG_CONTENTS.c_str(),
                                    JESTUREPIPE_CONFIG_CONTENTS.size()));

    const std::map<std::string, mediapipe::Packet> side_packets = {
        {"palm_model_path",
         mediapipe::MakePacket<std::string>(palm_model_lite_path)
             .At(mediapipe::Timestamp(0))},
        {"landmark_model_path",
         mediapipe::MakePacket<std::string>(hand_model_lite_path)
             .At(mediapipe::Timestamp(0))},
    };

    MP_RETURN_IF_ERROR(graph->Initialize(config, side_packets));

    return absl::OkStatus();
}
}  // namespace jesturepipe