#include "jesturepipe/gesture/recognizer.h"
#include "jesturepipe/gesture/frame_count.h"
#include <ctime>
namespace jesturepipe {
GestureRecognizer::GestureRecognizer() : comp(0) {}

GestureRecognizer::GestureRecognizer(std::shared_ptr<GestureLibrary> library,
                                     double threshold)
    : library(std::move(library)), comp(threshold) {}

GestureRecognizer::GestureRecognizer(GestureRecognizer &&other) : comp(0) {
    *this = std::move(other);
}

GestureRecognizer &GestureRecognizer::operator=(GestureRecognizer &&other) {
    if (this != &other) {
        library = std::move(other.library);
        comp = std::move(other.comp);
        matchers = std::move(other.matchers);
    }

    return *this;
}

void GestureRecognizer::Reset() { matchers.clear(); }

absl::optional<int> GestureRecognizer::ProcessFrame(const GestureFrame &frame) {
    absl::optional<int> matched;
    
    // Check if this is the first frame in any gesture
    {
        // Acquire read lock on library
        auto lk = library->RLock();
        for (const auto &[id, gesture] : *library) {
            if (comp(gesture.frames->at(0), frame)) {
                matchers.push_back(GestureMatcher(id, gesture, &comp));
            }
        }
    }

    // Remove all matchers that failed to match
    matchers.remove_if(
        [&frame](GestureMatcher &matcher) { return !matcher.Advance(frame); });

    // Check if we've had any matches
    for (auto &matcher : matchers) {
        matched = matcher.Matches();
        FrameCount &instance = FrameCount::get_instance();
        if (matched.has_value()) {
            if (*matched == 1) {
                instance.slide_left_count++;
                if (instance.slide_left_count == 1){
                    instance.slide_left_count = 0;
                    instance.cool_down_init_time = absl::Now();
                    instance.should_cool_down = true;
                    std::cout << "id: " << *matched << std::endl;
                    break;
                }
                *matched = -100;
            }
            else 
                instance.slide_left_count = 0;

            if (*matched == 5) {
                instance.slide_right_count++;    
                if (instance.slide_right_count == 1){
                    instance.slide_right_count = 0;
                    instance.cool_down_init_time = absl::Now();
                    instance.should_cool_down = true;
                    std::cout << "id: " << *matched << std::endl;
                    break;
                }
                *matched = -100;
            }        
            else
                instance.slide_right_count = 0; 
            
            instance.cool_down_init_time = absl::Now();
            instance.should_cool_down = true;
            std::cout << "id: " << *matched << std::endl;
            break;
        }
    }
    // If we found a match, remove all matchers
    if (matched.has_value()) matchers.clear();
    return matched;
}

GestureRecognizer::GestureMatcher::GestureMatcher(
    int id, Gesture gesture, GestureFrame::Comparator *comp)
    : at(0), id(id), gesture(gesture), comp(comp) {}

bool GestureRecognizer::GestureMatcher::Advance(const GestureFrame &frame) {
    if (at < 0 || at >= gesture.frames->size()) return false;

    if ((*comp)(gesture.frames->at(at), frame)) {
        at += 1;
        return true;
    } else {
        at = -1;
        return false;
    }
}

absl::optional<int> GestureRecognizer::GestureMatcher::Matches() {
    absl::optional<int> match;
    if (at == gesture.frames->size()) match = id;
    
    return match;
}
}  // namespace jesturepipe