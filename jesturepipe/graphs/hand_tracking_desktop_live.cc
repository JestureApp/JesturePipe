#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/port/file_helpers.h"

namespace jesturepipe {
absl::Status hand_tracking_desktop_live_graph(mediapipe::CalculatorGraph* graph) {
    // TODO: get file contents dynamically
    absl::string_view filename = "/home/storm/Workspace/Jesture/JesturePipe/bazel-bin/external/mediapipe/mediapipe/graphs/hand_tracking/hand_tracking_desktop_live.binarypb"; 
    std::string graph_config_contents;

    MP_RETURN_IF_ERROR(mediapipe::file::GetContents(filename, &graph_config_contents));

    mediapipe::CalculatorGraphConfig config;

    RET_CHECK(config.ParseFromArray(graph_config_contents.c_str(), graph_config_contents.size()));

    MP_RETURN_IF_ERROR(graph->Initialize(config));

    return absl::OkStatus();
}

}  // namespace jesturepipe