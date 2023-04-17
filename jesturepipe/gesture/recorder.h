#ifndef JESTUREPIPE_GESTURE_RECORDER_H
#define JESTUREPIPE_GESTURE_RECORDER_H

#include "jesturepipe/gesture/gesture.h"
#include <iostream>
namespace jesturepipe {

class GestureRecorder {
   public:
    void AddFrame(GestureFrame frame);
    Gesture Finish();
    // Gesture GestureRecorder::FrameFilter(Gesture gesture);
   private:
    Gesture gesture;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_RECORDER_H