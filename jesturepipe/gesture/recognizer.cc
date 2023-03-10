#include "jesturepipe/gesture/recognizer.h"

namespace jesturepipe {
GestureRecognizer::GestureRecognizer(std::shared_ptr<GestureLibrary> library,
                                     double threshold)
    : library(std::move(library)), comp(threshold) {}

absl::optional<int> GestureRecognizer::ProcessFrame(const GestureFrame &frame) {
    absl::optional<int> matched;

    // Check if this is the first frame in any gesture
    {
        // Acquire read lock on library
        auto lk = library->RLock();
        for (const auto &[id, gesture] : *library) {
            if (comp(gesture.frames[0], frame)) {
                matchers.push_back(GestureMatcher(id, gesture, &comp));
            }
        }
    }

    // Remove all matchers that failed to match
    matchers.remove_if(
        [&frame](GestureMatcher &matcher) { return matcher.Advance(frame); });

    // Check if we've had any matches
    for (auto &matcher : matchers) {
        matched = matcher.Matches();

        if (matched.has_value()) break;
    }

    // If we found a match, remove all matchers
    if (matched.has_value()) matchers.clear();

    return matched;
}

GestureRecognizer::GestureMatcher::GestureMatcher(
    int id, Gesture gesture, GestureFrame::ThresholdComparator *comp)
    : at(0), id(id), gesture(gesture), comp(comp) {}

bool GestureRecognizer::GestureMatcher::Advance(const GestureFrame &frame) {
    if (at < 0 || at >= gesture.frames.size()) return false;

    if ((*comp)(gesture.frames[at], frame)) {
        at += 1;
        return true;
    } else {
        at = -1;
        return false;
    }
}

absl::optional<int> GestureRecognizer::GestureMatcher::Matches() {
    absl::optional<int> match;

    if (at == gesture.frames.size()) match = id;

    return match;
}
}  // namespace jesturepipe