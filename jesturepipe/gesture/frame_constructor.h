#ifndef JESTUREPIPE_GESTURE_FRAME_CONSTRUCTOR_H
#define JESTUREPIPE_GESTURE_FRAME_CONSTRUCTOR_H

#include "absl/time/time.h"
#include "absl/types/optional.h"
#include "jesturepipe/gesture/gesture.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {

class GestureFrameConstructor {
   public:
    GestureFrameConstructor(double thresh = 50);

    GestureFrameConstructor(GestureFrameConstructor&);
    GestureFrameConstructor& operator=(GestureFrameConstructor&);

    GestureFrameConstructor(GestureFrameConstructor&&);
    GestureFrameConstructor& operator=(GestureFrameConstructor&&);

    void Reset();

    absl::optional<GestureFrame> OnLandmarks(
        const mediapipe::NormalizedLandmarkList& landmarks, absl::Time time);

   private:
    GestureFrame::Comparator frame_comp;

    absl::optional<HandShape> init_shape;
    absl::optional<double> init_direction;
    absl::optional<std::tuple<double, double>> init_com;
    absl::Time init_time;
    absl::optional<std::tuple<double, double>> init_wrist_landmark;
    bool frame_emitted;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_FRAME_CONSTRUCTOR_H