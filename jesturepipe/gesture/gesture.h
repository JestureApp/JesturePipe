#ifndef JESTUREPIPE_GESTURE_GESTURE_H
#define JESTUREPIPE_GESTURE_GESTURE_H

#include <memory>
#include <vector>

#include "absl/types/optional.h"

namespace jesturepipe {
/// \brief Represents the shape of the hand. Contains all information
/// responsible for comparing hand shapes between frames.
typedef struct HandShape {
    /// \brief A comparator functor for comparing `HandShape`s.
    ///
    /// Returns `true` if the `HandShape`s should be considered equal, or
    /// `false` otherwise.
    struct Comparator {
        Comparator() = delete;
        Comparator(double thresh) noexcept;

        bool operator()(const HandShape& a, const HandShape& b);

        double thresh;
    };

    double index_direction;
    double middle_direction;
    double ring_direction;
    double pinky_direction;
    double thumb_direction;
} HandShape;

/// \brief Represents a single frame of a gesture.
typedef struct GestureFrame {
    struct Comparator {
       public:
        Comparator() = delete;
        Comparator(double thresh) noexcept;

        bool operator()(const GestureFrame& a, const GestureFrame& b);

        double thresh;
        HandShape::Comparator hand_shape_comp;
    };

    HandShape hand_shape;
    absl::optional<double> movement_direction;
} GestureFrame;

class Gesture {
   public:
    static Gesture Stop();
    static Gesture SlideLeft();

    Gesture();
    Gesture(std::vector<GestureFrame>&& frames);

    Gesture(const Gesture& other) noexcept;
    Gesture& operator=(const Gesture& other) noexcept;

    Gesture(Gesture&& other) noexcept;
    Gesture& operator=(Gesture&& other) noexcept;

    std::shared_ptr<std::vector<GestureFrame>> frames;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_GESTURE_H