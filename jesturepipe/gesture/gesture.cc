#include "jesturepipe/gesture/gesture.h"

#include <math.h>

namespace jesturepipe {

namespace {
constexpr int WRIST = 0;
constexpr int THUMB_CMC = 1;
constexpr int THUMB_MCP = 2;
constexpr int THUMB_IP = 3;
constexpr int THUMB_TIP = 4;
constexpr int INDEX_FINGER_MCP = 5;
constexpr int INDEX_FINGER_PIP = 6;
constexpr int INDEX_FINGER_DIP = 7;
constexpr int INDEX_FINGER_TIP = 8;
constexpr int MIDDLE_FINGER_MCP = 9;
constexpr int MIDDLE_FINGER_PIP = 10;
constexpr int MIDDLE_FINGER_DIP = 11;
constexpr int MIDDLE_FINGER_TIP = 12;
constexpr int RING_FINGER_MCP = 13;
constexpr int RING_FINGER_PIP = 14;
constexpr int RING_FINGER_DIP = 15;
constexpr int RING_FINGER_TIP = 16;
constexpr int PINKY_MCP = 17;
constexpr int PINKY_PIP = 18;
constexpr int PINKY_DIP = 19;
constexpr int PINKY_TIP = 20;
}  // namespace

constexpr bool in_threshold(double a, double b, double thresh) {
    return abs(a - b) <= thresh;
}

double GetAngle(double dx, double dy) {
    double theta = atan2(-dy, dx);
    return theta * (180 / M_PI);
}

double GetAngle(mediapipe::NormalizedLandmark from,
                mediapipe::NormalizedLandmark to) {
    return GetAngle(to.x() - from.x(), to.y() - from.y());
}

HandShape HandShape::FromLandmarks(
    const mediapipe::NormalizedLandmarkList& landmarks) noexcept {
    auto landmark = landmarks.landmark();

    double index_direction =
        GetAngle(landmark[INDEX_FINGER_PIP], landmark[INDEX_FINGER_TIP]);

    double middle_direction =
        GetAngle(landmark[MIDDLE_FINGER_PIP], landmark[MIDDLE_FINGER_TIP]);

    double ring_direction =
        GetAngle(landmark[RING_FINGER_PIP], landmark[RING_FINGER_TIP]);

    double pinky_direction = GetAngle(landmark[PINKY_PIP], landmark[PINKY_TIP]);

    double thumb_direction = GetAngle(landmark[THUMB_IP], landmark[THUMB_TIP]);

    return HandShape{
        .index_direction = index_direction,
        .middle_direction = middle_direction,
        .ring_direction = ring_direction,
        .pinky_direction = pinky_direction,
        .thumb_direction = thumb_direction,
    };
}

bool HandShape::are_similar(const HandShape& a, const HandShape& b,
                            double thresh) noexcept {
    double angle_thresh = thresh * 360;

    return in_threshold(a.index_direction, b.index_direction, angle_thresh) &&
           in_threshold(a.middle_direction, b.middle_direction, angle_thresh) &&
           in_threshold(a.ring_direction, b.ring_direction, angle_thresh) &&
           in_threshold(a.pinky_direction, b.pinky_direction, angle_thresh) &&
           in_threshold(a.thumb_direction, b.thumb_direction, angle_thresh);
}

GestureFrame::Comparator::Comparator(double thresh) noexcept : thresh(thresh) {}

bool GestureFrame::Comparator::operator()(const GestureFrame& a,
                                          const GestureFrame& b) {
    double angle_thresh = thresh * 360;

    return HandShape::are_similar(a.hand_shape, b.hand_shape, thresh) &&
           in_threshold(a.movement_direction, b.movement_direction,
                        angle_thresh);
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