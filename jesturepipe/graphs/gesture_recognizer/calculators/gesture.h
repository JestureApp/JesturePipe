#ifndef __H_GESTURE_FEATURE__
#define __H_GESTURE_FEATURE__

namespace jesturepipe {
typedef enum FingerDirection { Left, Right, Up, Down } FindDirection;

typedef struct GestureFeature {
    FingerDirection index;
    FingerDirection middle;
    FingerDirection ring;
    FingerDirection pinky;
    FingerDirection thumb;
} GestureFeature;

typedef enum Gesture { Peace, Unknown } Gesture;

}  // namespace jesturepipe

#endif  // __H_GESTURE_FEATURE__