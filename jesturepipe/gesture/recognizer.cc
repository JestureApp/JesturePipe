#include "jesturepipe/gesture/recognizer.h"
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
            // if (gesture.frames->at(0).movement_direction.has_value())
            //         std::cout << "frame 0 movement_direction: "
            //           << gesture.frames->at(0).movement_direction.value() << std::endl;
            // if (frame.movement_direction.has_value())
            //         std::cout << "our frame movement_direction: "
                    //   << frame.movement_direction.value() << std::endl;
 
            if (comp(gesture.frames->at(0), frame)) {
                // std::cout << "Matched first pos " << id << std::endl;
                matchers.push_back(GestureMatcher(id, gesture, &comp));
            }
        }
        
    }
   
    // Remove all matchers that failed to match
    matchers.remove_if(
        [&frame](GestureMatcher &matcher) { 
            // std::cout << "advance: " << !matcher.Advance(frame) << std::endl;
            return !matcher.Advance(frame); 
            });


    // Check if we've had any matches
    for (auto &matcher : matchers) {
        matched = matcher.Matches();
        if (matched.has_value()) {
            // Debug:
            std::cout << "id: " << *matched << std::endl;
            break;
        }
    }
    // If we found a match, remove all matchers
    if (matched.has_value()) {
        std::cout << "CLEAR MATCHER" << std::endl
        matchers.clear();
    }
    return matched;
}

GestureRecognizer::GestureMatcher::GestureMatcher(
    int id, Gesture gesture, GestureFrame::Comparator *comp)
    : at(0), id(id), gesture(gesture), comp(comp) {}

bool GestureRecognizer::GestureMatcher::Advance(const GestureFrame &frame) {
    std::cout << "Enter Frame No. " << at << std::endl;
    if (at < 0 || at >= gesture.frames->size()){
        std::cout << "FLUSH" << std::endl;
        return false;
    }
    // if (frame.movement_direction.has_value())
    //                 std::cout << "our frame movement_direction: "
    //                   << frame.movement_direction.value() << std::endl;
    if ((*comp)(gesture.frames->at(at), frame)) {
        std::cout << "Matched frame at index: " << at << std::endl;
        at += 1;
        return true;
    } else {
            std::cout << "FLUSH" << std::endl;
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