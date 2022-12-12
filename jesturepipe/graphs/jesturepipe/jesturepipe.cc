
#include "jesturepipe/graphs/jesturepipe/jesturepipe.h"

#include "jesturepipe/graphs/jesturepipe/jesturepipe_binary_graph.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {
absl::Status jesturepipe_graph(mediapipe::CalculatorGraph* graph) {
    mediapipe::CalculatorGraphConfig config;

    RET_CHECK(config.ParseFromArray(JESTUREPIPE_CONFIG_CONTENTS.c_str(),
                                    JESTUREPIPE_CONFIG_CONTENTS.size()));

    MP_RETURN_IF_ERROR(graph->Initialize(config));

    return absl::OkStatus();
}

absl::Status jesturepipe_graph(
    mediapipe::CalculatorGraph* graph,
    const std::map<std::string, mediapipe::Packet>& side_packets) {
    mediapipe::CalculatorGraphConfig config;

    RET_CHECK(config.ParseFromArray(JESTUREPIPE_CONFIG_CONTENTS.c_str(),
                                    JESTUREPIPE_CONFIG_CONTENTS.size()));

    MP_RETURN_IF_ERROR(graph->Initialize(config, side_packets));

    return absl::OkStatus();
}
}  // namespace jesturepipe