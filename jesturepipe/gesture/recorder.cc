#include "jesturepipe/gesture/recorder.h"

namespace jesturepipe {
GestureRecorder::GestureRecorder() noexcept : gesture(-1) {}

Gesture GestureRecorder::finish() noexcept {
    Gesture ret(gesture);

    gesture = Gesture(-1);

    return ret;
}

void GestureRecorder::addFrame(GestureFrame frame) noexcept {
    gesture.frames.push_back(frame);
}
}  // namespace jesturepipe