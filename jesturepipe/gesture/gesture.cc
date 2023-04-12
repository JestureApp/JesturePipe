#include "jesturepipe/gesture/gesture.h"

#include <math.h>

#include <iomanip>

namespace jesturepipe {

Gesture Gesture::Pause() {
    return Gesture(std::vector<GestureFrame>{GestureFrame{HandShape{
        .index_direction = 90,
        .middle_direction = 90,
        .ring_direction = 270,
        .pinky_direction = 270,
        .thumb_direction = 90,
    }}});
}

Gesture Gesture::ThumbsUp() {
    return Gesture(std::vector<GestureFrame>{GestureFrame{HandShape{
        .index_direction = 180,
        .middle_direction = 180,
        .ring_direction = 180,
        .pinky_direction = 180,
        .thumb_direction = 90,
    }}});
}

Gesture Gesture::GrabMouse() {
    return Gesture(std::vector<GestureFrame>{GestureFrame{HandShape{
        .index_direction = 270,
        .middle_direction = 270,
        .ring_direction = 270,
        .pinky_direction = 270,
        .thumb_direction = 90,
    }}});
}

Gesture Gesture::LeaveMouse() {
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

Gesture Gesture::SlideRight() {
    return Gesture(
        std::vector<GestureFrame>{GestureFrame{.hand_shape =
                                                   HandShape{
                                                       .index_direction = 90,
                                                       .middle_direction = 90,
                                                       .ring_direction = 90,
                                                       .pinky_direction = 90,
                                                       .thumb_direction = 90,
                                                   },
                                               .movement_direction = 0}});
}

Gesture Gesture::SlideUp() {
    return Gesture(
        std::vector<GestureFrame>{GestureFrame{.hand_shape =
                                                   HandShape{
                                                       .index_direction = 180,
                                                       .middle_direction = 180,
                                                       .ring_direction = 180,
                                                       .pinky_direction = 180,
                                                       .thumb_direction = 180,
                                                   },
                                               .movement_direction = 90}});
}

Gesture Gesture::SlideDown() {
    return Gesture(
        std::vector<GestureFrame>{GestureFrame{.hand_shape =
                                                   HandShape{
                                                       .index_direction = 180,
                                                       .middle_direction = 180,
                                                       .ring_direction = 180,
                                                       .pinky_direction = 180,
                                                       .thumb_direction = 180,
                                                   },
                                               .movement_direction = 270}});
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
    GestureFrame tempA = a;
    GestureFrame tempB = b;
    if (tempA.movement_direction.has_value())
        if (tempA.movement_direction.value() > 300)
            tempA.movement_direction = 360 - tempA.movement_direction.value();

    if (tempB.movement_direction.has_value())
        if (tempB.movement_direction.value() > 300)
            tempB.movement_direction = 360 - tempB.movement_direction.value();

    return hand_shape_comp(a.hand_shape, b.hand_shape) &&
           ((!a.movement_direction.has_value() &&
             !b.movement_direction.has_value()) ||
            (a.movement_direction.has_value() &&
             b.movement_direction.has_value() &&
             in_threshold(tempA.movement_direction.value(),
                          tempB.movement_direction.value(), angle_thresh)));
}

std::ostream& operator<<(std::ostream& out, GestureFrame const& frame) {
    auto default_precision = out.precision();

    out << std::setprecision(3);

    out << "{";

    if (frame.movement_direction.has_value()) {
        out << "movement_direction = " << frame.movement_direction.value()
            << ", ";
    }

    out << "index_direction = " << frame.hand_shape.index_direction << ", ";
    out << "middle_direction = " << frame.hand_shape.middle_direction << ", ";
    out << "ring_direction = " << frame.hand_shape.ring_direction << ", ";
    out << "pinky_direction = " << frame.hand_shape.pinky_direction << ", ";
    out << "thumb_direction = " << frame.hand_shape.thumb_direction;

    out << "}";

    out << std::setprecision(default_precision);

    return out;
}

Gesture::Gesture() : frames(std::make_shared<std::vector<GestureFrame>>()) {}

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

std::ostream& operator<<(std::ostream& out, Gesture const& gesture) {
    out << "[";

    for (auto frame : *gesture.frames) {
        out << frame;
    }

    out << "]";

    return out;
}

}  // namespace jesturepipe