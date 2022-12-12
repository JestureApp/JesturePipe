#ifndef __H__GRAPHS_JESTUREPIPE_JESTUREPIPE_H__
#define __H__GRAPHS_JESTUREPIPE_JESTUREPIPE_H__

#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {
absl::Status jesturepipe_graph(mediapipe::CalculatorGraph* graph);
absl::Status jesturepipe_graph(
    mediapipe::CalculatorGraph* graph,
    const std::map<std::string, mediapipe::Packet>& side_packets);
}  // namespace jesturepipe

#endif  // __H__GRAPHS_JESTUREPIPE_JESTUREPIPE_H__