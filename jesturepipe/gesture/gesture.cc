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

constexpr double ANGLE_THRESHOLD = 20;
}  // namespace

Gesture::Gesture(int id) noexcept : id(id) {}

Gesture::Gesture(const Gesture& other) noexcept
    : id(other.id), frames(other.frames) {}

Gesture& Gesture::operator=(const Gesture& other) noexcept {
    if (this != &other) {
        frames = other.frames;
        id = other.id;
    }

    return *this;
}

GestureFrame& Gesture::operator[](unsigned long index) noexcept {
    return frames[index];
}

void Gesture::AddFrame(GestureFrame frame) noexcept { frames.push_back(frame); }

unsigned long Gesture::size() noexcept { return frames.size(); }

double GetAngle(double dx, double dy) {
    double theta = atan2(-dy, dx);
    return theta * (180 / M_PI);
}

double GetAngle(mediapipe::NormalizedLandmark from,
                mediapipe::NormalizedLandmark to) {
    return GetAngle(to.x() - from.x(), to.y() - from.y());
}

GestureFrame::GestureFrame(double index_direction, double middle_direction,
                           double ring_direction, double pinky_direction,
                           double thumb_direction) noexcept {
    this->index_direction = index_direction;
    this->middle_direction = middle_direction;
    this->ring_direction = ring_direction;
    this->pinky_direction = pinky_direction;
    this->thumb_direction = thumb_direction;
}

GestureFrame GestureFrame::FromLandmarks(
    mediapipe::NormalizedLandmarkList& landmarks) noexcept {
    auto landmark = landmarks.landmark();

    double index_direction =
        GetAngle(landmark[INDEX_FINGER_PIP], landmark[INDEX_FINGER_TIP]);

    double middle_direction =
        GetAngle(landmark[MIDDLE_FINGER_PIP], landmark[MIDDLE_FINGER_TIP]);

    double ring_direction =
        GetAngle(landmark[RING_FINGER_PIP], landmark[RING_FINGER_TIP]);

    double pinky_direction = GetAngle(landmark[PINKY_PIP], landmark[PINKY_TIP]);

    double thumb_direction = GetAngle(landmark[THUMB_IP], landmark[THUMB_TIP]);

    return GestureFrame(index_direction, middle_direction, ring_direction,
                        pinky_direction, thumb_direction);
}

bool GestureFrame::isSame(const GestureFrame& other) const noexcept {
    return abs(index_direction - other.index_direction) <= ANGLE_THRESHOLD &&
           abs(middle_direction - other.middle_direction) <= ANGLE_THRESHOLD &&
           abs(ring_direction - other.ring_direction) <= ANGLE_THRESHOLD &&
           abs(pinky_direction - other.pinky_direction) <= ANGLE_THRESHOLD &&
           abs(thumb_direction - other.thumb_direction) <= ANGLE_THRESHOLD;
}

bool operator==(const GestureFrame& frame1,
                const GestureFrame& frame2) noexcept {
    return frame1.isSame(frame2);
}

bool operator!=(const GestureFrame& frame1,
                const GestureFrame& frame2) noexcept {
    return !(frame1 == frame2);
}
}  // namespace jesturepipe