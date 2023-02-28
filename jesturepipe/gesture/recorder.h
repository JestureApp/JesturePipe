#ifndef JESTUREPIPE_GESTURE_RECORDER_H
#define JESTUREPIPE_GESTURE_RECORDER_H

#include "jesturepipe/gesture/gesture.h"

namespace jesturepipe {

class GestureRecorder {
   public:
    GestureRecorder() noexcept;

    Gesture finish() noexcept;

    void addFrame(GestureFrame frame) noexcept;

   private:
    Gesture gesture;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_RECORDER_H