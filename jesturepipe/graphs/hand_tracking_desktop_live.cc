#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "tools/cpp/runfiles/runfiles.h"

namespace jesturepipe {
using bazel::tools::cpp::runfiles::Runfiles;

absl::Status hand_tracking_desktop_live_graph(const std::string& arg0, mediapipe::CalculatorGraph* graph) {
    std::string error;
    std::unique_ptr<Runfiles> runfiles(Runfiles::Create(arg0, &error));

    if (runfiles == nullptr) {
        return absl::NotFoundError(error);
    }

    // TODO: get file contents dynamically
    std::string filename = runfiles->Rlocation("mediapipe/mediapipe/graphs/hand_tracking/hand_tracking_desktop_live.binarypb"); 
    LOG(INFO) << "Loading graph from " << filename;

    std::string graph_config_contents;

    MP_RETURN_IF_ERROR(mediapipe::file::GetContents(filename, &graph_config_contents));

    mediapipe::CalculatorGraphConfig config;

    RET_CHECK(config.ParseFromArray(graph_config_contents.c_str(), graph_config_contents.size()));

    MP_RETURN_IF_ERROR(graph->Initialize(config));

    return absl::OkStatus();
}

}  // namespace jesturepipe