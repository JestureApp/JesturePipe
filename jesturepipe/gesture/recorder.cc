#include "jesturepipe/gesture/recorder.h"

namespace jesturepipe {

void GestureRecorder::AddFrame(GestureFrame frame) {
    gesture.frames->push_back(frame);
}

Gesture GestureRecorder::Finish() { return gesture; }

}  // namespace jesturepipe