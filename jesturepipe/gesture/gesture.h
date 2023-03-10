#ifndef JESTUREPIPE_GESTURE_GESTURE_H
#define JESTUREPIPE_GESTURE_GESTURE_H

#include <vector>

#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {
typedef struct GestureFrame {
    static GestureFrame FromLandmarks(
        const mediapipe::NormalizedLandmarkList& landmarks) noexcept;

    /// \brief Measures the similarity between two frames.
    /// \return The similarity measure. A value between 0 and 1.
    static double similarity(const GestureFrame& a, const GestureFrame& b);

    /// \brief Measures the difference between two frames.
    /// \return The difference measure. A value between 0 and 1.
    static double difference(const GestureFrame& a, const GestureFrame& b);

    class ThresholdComparator {
       public:
        ThresholdComparator() = delete;
        ThresholdComparator(double thresh) noexcept;

        bool operator()(const GestureFrame& a, const GestureFrame& b);

       private:
        double thresh;
    };
} GestureFrame;

class Gesture {
   public:
    Gesture() = default;
    Gesture(std::vector<GestureFrame>&& frames);

    Gesture(const Gesture& other) noexcept;
    Gesture& operator=(const Gesture& other) noexcept;

    Gesture(Gesture&& other) noexcept;
    Gesture& operator=(Gesture&& other) noexcept;

    std::vector<GestureFrame> frames;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_GESTURE_H