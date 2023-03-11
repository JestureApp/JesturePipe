#ifndef JESTUREPIPE_GESTURE_GESTURE_H
#define JESTUREPIPE_GESTURE_GESTURE_H

#include <vector>

#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {
typedef struct HandShape {
    static HandShape FromLandmarks(
        const mediapipe::NormalizedLandmarkList& landmarks) noexcept;

    static bool are_similar(const HandShape& a, const HandShape& b,
                            double thresh) noexcept;

    double index_direction;
    double middle_direction;
    double ring_direction;
    double pinky_direction;
    double thumb_direction;
} HandShape;

typedef struct GestureFrame {
    class Comparator {
       public:
        Comparator() = delete;
        Comparator(double thresh) noexcept;

        bool operator()(const GestureFrame& a, const GestureFrame& b);

       private:
        double thresh;
    };

    HandShape hand_shape;
    double movement_direction;
} GestureFrame;

class Gesture {
   public:
    Gesture() = default;
    Gesture(std::vector<GestureFrame>&& frames);

    Gesture(const Gesture& other) noexcept;
    Gesture& operator=(const Gesture& other) noexcept;

    Gesture(Gesture&& other) noexcept;
    Gesture& operator=(Gesture&& other) noexcept;

    std::shared_ptr<std::vector<GestureFrame>> frames;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_GESTURE_H