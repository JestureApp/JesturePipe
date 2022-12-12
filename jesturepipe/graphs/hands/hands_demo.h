#pragma once

#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {
    absl::Status hand_tracking_desktop_live_graph(const std::string& arg0, mediapipe::CalculatorGraph* graph);
};  // namespace jesturepipe
