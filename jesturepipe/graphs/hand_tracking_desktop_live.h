#pragma once

#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {
    absl::Status hand_tracking_desktop_live_graph(mediapipe::CalculatorGraph* graph);
};  // namespace jesturepipe
