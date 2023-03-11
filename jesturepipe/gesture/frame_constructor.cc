#include "jesturepipe/gesture/frame_constructor.h"

#include <assert.h>
#include <math.h>

#include <iostream>

namespace jesturepipe {

namespace {
constexpr double STATIONARY_DIST_THRESH = 0.1;
const absl::Duration STATIONARY_TIME_THRESH = absl::Seconds(0.5);

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

double get_angle(double dx, double dy) {
    double theta = atan2(-dy, dx);

    theta *= (180 / M_PI);

    if (theta < 0) theta += 360;

    return theta;
}

double get_angle(const mediapipe::NormalizedLandmark& from,
                 const mediapipe::NormalizedLandmark& to) {
    return get_angle(to.x() - from.x(), to.y() - from.y());
}

HandShape hand_shape_from_landmarks(
    const mediapipe::NormalizedLandmarkList& landmarks) {
    auto landmark = landmarks.landmark();

    double index_direction =
        get_angle(landmark[INDEX_FINGER_PIP], landmark[INDEX_FINGER_TIP]);

    double middle_direction =
        get_angle(landmark[MIDDLE_FINGER_PIP], landmark[MIDDLE_FINGER_TIP]);

    double ring_direction =
        get_angle(landmark[RING_FINGER_PIP], landmark[RING_FINGER_TIP]);

    double pinky_direction =
        get_angle(landmark[PINKY_PIP], landmark[PINKY_TIP]);

    double thumb_direction = get_angle(landmark[THUMB_IP], landmark[THUMB_TIP]);

    return HandShape{
        .index_direction = index_direction,
        .middle_direction = middle_direction,
        .ring_direction = ring_direction,
        .pinky_direction = pinky_direction,
        .thumb_direction = thumb_direction,
    };
}

std::tuple<double, double> landmarks_loc(
    const mediapipe::NormalizedLandmarkList& landmarks) {
    //
    auto landmark = landmarks.landmark();

    int n = landmarks.landmark_size();

    double x_sum = 0;
    double y_sum = 0;

    for (int i = 0; i < n; i++) {
        x_sum += landmark[i].x();
        y_sum += landmark[i].y();
    }

    double x_cm = x_sum / n;
    double y_cm = y_sum / n;

    return std::make_tuple(x_cm, y_cm);
}

GestureFrameConstructor::GestureFrameConstructor(double thresh)
    : frame_comp(thresh), frame_emitted(false) {}

GestureFrameConstructor& GestureFrameConstructor::operator=(
    GestureFrameConstructor& other) {
    if (this != &other) {
        frame_comp = other.frame_comp;
        init_direction = other.init_direction;
        init_loc = other.init_loc;
        init_time = other.init_time;
        frame_emitted = other.frame_emitted;
    }

    return *this;
}

GestureFrameConstructor::GestureFrameConstructor(GestureFrameConstructor& other)
    : frame_comp(0) {
    *this = other;
}

GestureFrameConstructor& GestureFrameConstructor::operator=(
    GestureFrameConstructor&& other) {
    if (this != &other) {
        init_shape = std::move(other.init_shape);
        init_direction = std::move(other.init_direction);
        init_loc = std::move(other.init_loc);
        init_time = std::move(other.init_time);

        frame_emitted = other.frame_emitted;
        other.frame_emitted = false;
    }

    return *this;
}

GestureFrameConstructor::GestureFrameConstructor(
    GestureFrameConstructor&& other)
    : frame_comp(0) {
    *this = std::move(other);
}

void GestureFrameConstructor::Reset() {
    init_shape.reset();
    init_direction.reset();
    init_loc.reset();
    init_time = absl::UnixEpoch();  // Shouldn't matter what this is set to
    frame_emitted = false;
}

absl::optional<GestureFrame> GestureFrameConstructor::OnLandmarks(
    const mediapipe::NormalizedLandmarkList& landmarks, absl::Time time) {
    absl::optional<GestureFrame> maybe_frame;

    HandShape new_shape = hand_shape_from_landmarks(landmarks);
    auto new_loc = landmarks_loc(landmarks);

    if (!init_shape.has_value()) {
        init_shape = new_shape;
        init_direction.reset();
        init_loc = new_loc;
        init_time = time;
        frame_emitted = false;

        // std::cout << "HERE1" << std::endl;

        return maybe_frame;
    }

    HandShape curr_shape = init_shape.value();
    auto curr_loc = init_loc.value();

    double dx = std::get<0>(new_loc) - std::get<0>(curr_loc);
    double dy = std::get<1>(new_loc) - std::get<1>(curr_loc);

    double dist = sqrt(dx * dx + dy * dy);

    GestureFrame curr_frame{curr_shape, init_direction};

    if (dist <= STATIONARY_DIST_THRESH) {
        if (!frame_emitted && time - init_time >= STATIONARY_TIME_THRESH) {
            // std::cout << "HERE2" << std::endl;
            maybe_frame = curr_frame;
            frame_emitted = true;
        }

        return maybe_frame;
    }

    double new_direction = get_angle(dx, dy);
    GestureFrame new_frame{new_shape, new_direction};

    if (!frame_comp(curr_frame, new_frame)) {
        // std::cout << "HERE3" << std::endl;
        maybe_frame = GestureFrame{curr_shape, new_direction};

        init_shape = new_shape;
        init_direction.reset();
        init_loc = new_loc;
        init_time = time;
        frame_emitted = false;
    } else if (!frame_emitted) {
        // std::cout << "HERE4" << std::endl;
        maybe_frame = GestureFrame{curr_shape, new_direction};
        frame_emitted = true;
    }

    return maybe_frame;
}

}  // namespace jesturepipe