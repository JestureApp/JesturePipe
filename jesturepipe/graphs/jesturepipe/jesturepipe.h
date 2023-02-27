#ifndef JESTUREPIPE_GRAPHS_JESTUREPIPE_JESTUREPIPE
#define JESTUREPIPE_GRAPHS_JESTUREPIPE_JESTUREPIPE

#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {
absl::Status jesturepipe_graph(mediapipe::CalculatorGraph* graph,
                               std::string palm_model_full_path,
                               std::string palm_model_lite_path,
                               std::string landmark_model_full_path,
                               std::string landmark_model_lite_path);

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GRAPHS_JESTUREPIPE_JESTUREPIPE