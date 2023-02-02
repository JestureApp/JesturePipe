#ifndef __H_GESTURE_FEATURE__
#define __H_GESTURE_FEATURE__

namespace jesturepipe {
typedef enum FingerDirection { Left, Right, Up, Down } FindDirection;

typedef struct GestureFeature {
    FingerDirection index_vertical;
    FingerDirection middle_vertical;
    FingerDirection ring_vertical;
    FingerDirection pinky_vertical;
    FingerDirection thumb_vertical;
    FingerDirection index_horizontal;
    FingerDirection middle_horizontal;
    FingerDirection ring_horizontal;
    FingerDirection pinky_horizontal;
    FingerDirection thumb_horizontal;
    FingerDirection thumb_index_vertical;
    double middle_angle;
};

typedef enum Gesture { Stop, Pause, Okay, Previous, Next, Custom, Unknown } Gesture;

}  // namespace jesturepipe

#endif  // __H_GESTURE_FEATURE__