#ifndef __H__GRAPHS_JESTUREPIPE_JESTUREPIPE_H__
#define __H__GRAPHS_JESTUREPIPE_JESTUREPIPE_H__

#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {
absl::Status jesturepipe_graph(mediapipe::CalculatorGraph* graph);
}  // namespace jesturepipe

#endif  // __H__GRAPHS_JESTUREPIPE_JESTUREPIPE_H__