#include "jesturepipe/gesture/recognizer.h"

namespace jesturepipe {

// GestureRecognizer::

void GestureRecognizer::addGesture(Gesture&& gesture) noexcept {
    GestureMatcher matcher(std::move(gesture));

    matchers.push_back(std::move(matcher));
}

absl::optional<int> GestureRecognizer::nextFrame(GestureFrame& frame) noexcept {
    absl::optional<int> matched;

    for (auto matcher : matchers) {
        if (matcher.matches(frame)) {
            matched = matcher.getGesture().id;
            break;
        }
    }

    if (matched.has_value()) reset();

    return matched;
}

void GestureRecognizer::reset() noexcept {
    for (auto matcher : matchers) {
        matcher.reset();
    }
}

GestureRecognizer::GestureMatcher::GestureMatcher(Gesture&& gesture) noexcept
    : gesture(std::move(gesture)), next(0){};

bool GestureRecognizer::GestureMatcher::matches(GestureFrame& frame) noexcept {
    if (frame == gesture.frames[next]) {
        next++;

        if (next == gesture.frames.size()) {
            next = 0;
            return true;
        } else
            return false;
    }

    next = 0;
    return false;
}

void GestureRecognizer::GestureMatcher::reset() noexcept { next = 0; }

Gesture& GestureRecognizer::GestureMatcher::getGesture() noexcept {
    return gesture;
}

}  // namespace jesturepipe