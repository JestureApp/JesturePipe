#include "jesturepipe/gesture/parser.h"

namespace jesturepipe {

GestureParser::GestureParser() noexcept {};

void GestureParser::AddGesture(Gesture gesture) noexcept {}

void GestureParser::consumeFrame(Gesture::KeyFrame frame) noexcept {
    if (!frame_ids.contains(frame)) return;
}

absl::optional<Gesture> GestureParser::terminateGesture() noexcept {
    absl::optional<Gesture> gesture;

    return gesture;
}

}  // namespace jesturepipe