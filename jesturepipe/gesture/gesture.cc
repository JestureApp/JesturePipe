#include "jesturepipe/gesture/gesture.h"

#include <math.h>

namespace jesturepipe {

Gesture Gesture::Stop() {
    return Gesture(std::vector<GestureFrame>{GestureFrame{HandShape{
        .index_direction = 90,
        .middle_direction = 90,
        .ring_direction = 90,
        .pinky_direction = 90,
        .thumb_direction = 90,
    }}});
}

Gesture Gesture::SlideLeft() {
    return Gesture(
        std::vector<GestureFrame>{GestureFrame{.hand_shape =
                                                   HandShape{
                                                       .index_direction = 90,
                                                       .middle_direction = 90,
                                                       .ring_direction = 90,
                                                       .pinky_direction = 90,
                                                       .thumb_direction = 90,
                                                   },
                                               .movement_direction = 180}});
}

constexpr bool in_threshold(double a, double b, double thresh) {
    return abs(a - b) <= thresh;
}

HandShape::Comparator::Comparator(double thresh) noexcept : thresh(thresh) {}

bool HandShape::Comparator::operator()(const HandShape& a, const HandShape& b) {
    double angle_thresh = thresh * 360;

    return in_threshold(a.index_direction, b.index_direction, angle_thresh) &&
           in_threshold(a.middle_direction, b.middle_direction, angle_thresh) &&
           in_threshold(a.ring_direction, b.ring_direction, angle_thresh) &&
           in_threshold(a.pinky_direction, b.pinky_direction, angle_thresh) &&
           in_threshold(a.thumb_direction, b.thumb_direction, angle_thresh);
}

GestureFrame::Comparator::Comparator(double thresh) noexcept
    : thresh(thresh), hand_shape_comp(thresh) {}

bool GestureFrame::Comparator::operator()(const GestureFrame& a,
                                          const GestureFrame& b) {
    double angle_thresh = thresh * 360;

    return hand_shape_comp(a.hand_shape, b.hand_shape) &&
           ((!a.movement_direction.has_value() &&
             !b.movement_direction.has_value()) ||
            (a.movement_direction.has_value() &&
             b.movement_direction.has_value() &&
             in_threshold(a.movement_direction.value(),
                          b.movement_direction.value(), angle_thresh)));
}

Gesture::Gesture(std::vector<GestureFrame>&& frames)
    : frames(std::make_shared<std::vector<GestureFrame>>(std::move(frames))) {}

Gesture::Gesture(const Gesture& other) noexcept { *this = other; }

Gesture& Gesture::operator=(const Gesture& other) noexcept {
    if (this != &other) {
        frames = other.frames;
    }

    return *this;
}

Gesture::Gesture(Gesture&& other) noexcept { *this = std::move(other); }

Gesture& Gesture::operator=(Gesture&& other) noexcept {
    if (this != &other) {
        frames = std::move(other.frames);
    }

    return *this;
}

}  // namespace jesturepipe