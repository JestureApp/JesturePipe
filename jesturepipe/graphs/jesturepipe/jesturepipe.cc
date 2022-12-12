
#include "jesturepipe/graphs/jesturepipe/jesturepipe.h"

#include "jesturepipe/graphs/jesturepipe/jesturepipe_binary_graph.h"

namespace jesturepipe {
absl::Status jesturepipe_graph(mediapipe::CalculatorGraph* graph) {
    mediapipe::CalculatorGraphConfig config;

    RET_CHECK(config.ParseFromArray(JESTUREPIPE_CONFIG_CONTENTS.c_str(),
                                    JESTUREPIPE_CONFIG_CONTENTS.size()));

    MP_RETURN_IF_ERROR(graph->Initialize(config));

    return absl::OkStatus();
}
}  // namespace jesturepipe