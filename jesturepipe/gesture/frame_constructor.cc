#include "jesturepipe/gesture/frame_constructor.h"

#include <assert.h>
#include <math.h>

#include <iostream>

#include "glog/logging.h"

namespace jesturepipe {

namespace {
constexpr double CENTER_OF_MASS_THRESH_LOW = 0.055;  // 0.055;
constexpr double CENTER_OF_MASS_THRESH_HIGH = 0.10;
constexpr absl::Duration COOL_DOWN_THRESH = absl::Seconds(2);
constexpr double DISPLACEMENT_THRESHOLD_STATIONARY = 0.06;
const absl::Duration STATIONARY_TIME_THRESH = absl::Seconds(0.75);  // 0.75
const absl::Duration DYNAMIC_TIME_THRESH = absl::Seconds(0.75);     // 0.75

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

double hand_displacement(const std::tuple<double, double> new_landmark,
                         const std::tuple<double, double> curr_landmark) {
    double dx = std::get<0>(curr_landmark) - std::get<0>(new_landmark);
    double dy = std::get<1>(curr_landmark) - std::get<1>(new_landmark);

    double displacement = sqrt(dx * dx + dy * dy);
    return displacement;
}

GestureFrameConstructor::GestureFrameConstructor(double thresh)
    : frame_comp(thresh), frame_emitted(false) {}

GestureFrameConstructor& GestureFrameConstructor::operator=(
    GestureFrameConstructor& other) {
    if (this != &other) {
        frame_comp = other.frame_comp;
        init_direction = other.init_direction;
        init_com = other.init_com;
        init_wrist_landmark = other.init_wrist_landmark;
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
        init_com = std::move(other.init_com);
        init_wrist_landmark = std::move(other.init_wrist_landmark);
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
    init_com.reset();
    init_time = absl::UnixEpoch();  // Shouldn't matter what this is set to
    init_wrist_landmark.reset();
    frame_emitted = false;
}
// a -> init_frame, b -> input_frame
bool CompareGestureFrame(GestureFrame& a, GestureFrame& b,
                         double angle_thresh) {
    if ((abs(a.hand_shape.index_direction - b.hand_shape.index_direction) <
         angle_thresh) &&
        (abs(a.hand_shape.middle_direction - b.hand_shape.middle_direction) <
         angle_thresh) &&
        (abs(a.hand_shape.ring_direction - b.hand_shape.ring_direction) <
         angle_thresh) &&
        (abs(a.hand_shape.pinky_direction - b.hand_shape.pinky_direction) <
         angle_thresh) &&
        (abs(a.hand_shape.thumb_direction - b.hand_shape.thumb_direction) <
         angle_thresh)) {
        if ((!a.movement_direction.has_value() &&
             !b.movement_direction.has_value())) {
            return true;
        } else if (a.movement_direction.has_value() &&
                   b.movement_direction.has_value()) {
            if (a.movement_direction.value() > 270)
                a.movement_direction = 360 - a.movement_direction.value();

            if (b.movement_direction.value() > 270)
                b.movement_direction = 360 - b.movement_direction.value();

            if (abs(a.movement_direction.value() -
                    b.movement_direction.value()) < angle_thresh)
                return true;
            } 
            else if (a.movement_direction.has_value() && b.movement_direction.has_value()){
                if (a.movement_direction.value() > 270)
                    a.movement_direction = 360 - a.movement_direction.value();

                if (b.movement_direction.value() > 270)
                    b.movement_direction = 360 - b.movement_direction.value();
                
                if (abs(a.movement_direction.value() - b.movement_direction.value()) < angle_thresh)
                    return true;
                // else
                //     std::cout << abs(a.movement_direction.value() - b.movement_direction.value()) << std::endl;
            } 
    }       
        
    return false;
}

absl::optional<GestureFrame> GestureFrameConstructor::OnLandmarks(
    const mediapipe::NormalizedLandmarkList& landmarks, absl::Time time) {
    HandShape input_shape = hand_shape_from_landmarks(landmarks);
    auto input_com = landmarks_loc(landmarks);
    absl::optional<GestureFrame> maybe_frame;
    absl::optional<GestureFrame> empty_frame;

    // initialize init_shape at the start of each frame
    if (!init_shape.has_value()) {
        init_shape = input_shape;
        init_direction.reset();
        init_com = input_com;
        init_time = time;
        frame_emitted = false;
        // return empty frame since frame is still being created
        return maybe_frame;
    }

    HandShape curr_shape = init_shape.value();
    auto curr_com = init_com.value();

    // calculating movement between the two input landmarks
    double dx = std::get<0>(input_com) - std::get<0>(curr_com);
    double dy = std::get<1>(input_com) - std::get<1>(curr_com);
    double direction = get_angle(dx, dy);
    double center = sqrt(dx * dx + dy * dy);

    // STATIONARY GESTURES
    if (center <= CENTER_OF_MASS_THRESH_LOW) {
        if (!frame_emitted && time - init_time >= STATIONARY_TIME_THRESH) {
            absl::optional<double> null_direction;
            null_direction.reset();
            maybe_frame = GestureFrame{input_shape, null_direction};
            frame_emitted = true;
        }
        return maybe_frame;
    }

        GestureFrame new_frame{input_shape, direction};   
        GestureFrame curr_frame{curr_shape, init_direction}; 
        
        // DYNAMIC GESTURES
        absl::Duration diff_time = (time - init_time);
        bool compGesture = CompareGestureFrame(curr_frame, new_frame, 40);
        if (!frame_emitted && compGesture && diff_time > DYNAMIC_TIME_THRESH) {
            frame_emitted = true;
            GestureFrame maybe_frame = GestureFrame{curr_shape, init_direction};
        //     std::cout << "Dynamic frame generated" << std::endl;

        // std::cout << "Recorded gesture with frames:" << std::endl;
        // std::cout << "GestureFrame{" << std::endl;
        // std::cout << "\tHandShape{" << std::endl;
        // std::cout << "\t\tindex_direction: " << maybe_frame.hand_shape.index_direction
        //         << std::endl;
        // std::cout << "\t\tmiddle_direction: "
        //         << maybe_frame.hand_shape.middle_direction << std::endl;
        // std::cout << "\t\tring_direction: " << maybe_frame.hand_shape.ring_direction
        //         << std::endl;
        // std::cout << "\t\tpinky_direction: " << maybe_frame.hand_shape.pinky_direction
        //         << std::endl;
        // std::cout << "\t\tthumb_direction: " << maybe_frame.hand_shape.thumb_direction
        //         << std::endl;
        // std::cout << "\t}" << std::endl;

        // if (maybe_frame.movement_direction.has_value())
        //     std::cout << "movement_direction: "
        //             << maybe_frame.movement_direction.value() << std::endl;
                    
        // std::cout << "}" << std::endl;
        
        return maybe_frame;
        } 
        else if (frame_emitted && compGesture) {
            // return empty_frame;
        }
        else if (!compGesture) {
            init_shape = input_shape;
            init_direction = direction;
            init_com = input_com;
            frame_emitted = false;
            init_time = time;
            // return empty_frame;
        }
        return empty_frame;
    } else if (!compGesture) {
        init_shape = input_shape;
        init_direction = direction;
        init_com = input_com;
        frame_emitted = false;
        init_time = time;
    }

}  // namespace jesturepipe