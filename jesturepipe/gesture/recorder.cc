#include "jesturepipe/gesture/recorder.h"
namespace jesturepipe {

// constexpr double ANGLE_THRESH = 40; // 0.055;

void GestureRecorder::AddFrame(GestureFrame frame) {
    gesture.frames->push_back(frame);
}

Gesture GestureRecorder::Finish() { 
    return gesture; 
}

}  // namespace jesturepipe