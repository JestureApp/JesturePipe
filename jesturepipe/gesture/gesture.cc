#include "jesturepipe/gesture/gesture.h"

namespace jesturepipe {

GestureFrame GestureFrame::FromLandmarks(
    const mediapipe::NormalizedLandmarkList& landmarks) noexcept {
    // TODO
    return GestureFrame{};
}

double GestureFrame::similarity(const GestureFrame& a, const GestureFrame& b) {
    // TODO
    return 0;
}

double GestureFrame::difference(const GestureFrame& a, const GestureFrame& b) {
    return 1 - GestureFrame::similarity(a, b);
}

GestureFrame::ThresholdComparator::ThresholdComparator(double thresh) noexcept
    : thresh(thresh) {}

bool GestureFrame::ThresholdComparator::operator()(const GestureFrame& a,
                                                   const GestureFrame& b) {
    return GestureFrame::difference(a, b) < thresh;
}

Gesture::Gesture(std::vector<GestureFrame>&& frames)
    : frames(std::move(frames)) {}

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