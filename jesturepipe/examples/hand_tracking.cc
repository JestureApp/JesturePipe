
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "mediapipe/framework/port/opencv_video_inc.h"


absl::Status RunGraph() {
    absl::string_view filename; // TODO: set this to the path of the graph binary
    std::string graph_config_contents;

    MP_RETURN_IF_ERROR(mediapipe::file::GetContents(filename, &graph_config_contents));

    mediapipe::CalculatorGraphConfig config;

    if (!config.ParseFromArray(graph_config_contents.c_str(), graph_config_contents.size())) {
        // TODO: more useful error type
        return absl::AbortedError("Failed to parse graph config contents");
    }

    mediapipe::CalculatorGraph graph;
    
    MP_RETURN_IF_ERROR(graph.Initialize(config));

    return absl::OkStatus();
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