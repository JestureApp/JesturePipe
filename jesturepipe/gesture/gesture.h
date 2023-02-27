#ifndef JESTUREPIPE_GESTURE_GESTURE_H
#define JESTUREPIPE_GESTURE_GESTURE_H

#include <functional>

#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {
class GestureFrame {
   public:
    /**
     * Constructs a new key frame from a list of hand landmarks.
     */
    static GestureFrame FromLandmarks(
        mediapipe::NormalizedLandmarkList& landmarks) noexcept;

    GestureFrame(double index_direction, double middle_direction,
                 double ring_direction, double pinky_direction,
                 double thumb_direction) noexcept;

    double index_direction;
    double middle_direction;
    double ring_direction;
    double pinky_direction;
    double thumb_direction;

   protected:
    bool isSame(const GestureFrame& frame1) const noexcept;

    friend bool operator==(const GestureFrame& frame1,
                           const GestureFrame& frame2) noexcept;
    friend bool operator!=(const GestureFrame& frame1,
                           const GestureFrame& frame2) noexcept;
};

class Gesture : public std::vector<GestureFrame> {};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_GESTURE_H