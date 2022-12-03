#include "absl/status/status.h"
#include "jesturepipe/graphs/jesturepipe/jesturepipe.h"
#include "mediapipe/framework/calculator_framework.h"

absl::Status RunGraph() {
    mediapipe::CalculatorGraph graph;
    MP_RETURN_IF_ERROR(jesturepipe::jesturepipe_graph(&graph));

    MP_RETURN_IF_ERROR(graph.StartRun({}));

    return graph.WaitUntilDone();
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
