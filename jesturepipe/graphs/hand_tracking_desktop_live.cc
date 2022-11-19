#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/status.h"
#include "jesturepipe/graphs/hands/hands_binary_graph.h"

namespace jesturepipe {

absl::Status hand_tracking_desktop_live_graph(const std::string& arg0, mediapipe::CalculatorGraph* graph) {
    mediapipe::CalculatorGraphConfig config;

    RET_CHECK(config.ParseFromArray(GRAPH_HANDS_CONFIG_CONTENTS.c_str(), GRAPH_HANDS_CONFIG_CONTENTS.size()));

    MP_RETURN_IF_ERROR(graph->Initialize(config));

    return absl::OkStatus();
}

}  // namespace jesturepipe