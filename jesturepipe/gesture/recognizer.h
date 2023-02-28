#ifndef JESTUREPIPE_GESTURE_PARSER_H
#define JESTUREPIPE_GESTURE_PARSER_H

#include <list>

#include "absl/types/optional.h"
#include "absl/types/variant.h"
#include "jesturepipe/gesture/gesture.h"

namespace jesturepipe {

class GestureRecognizer {
   public:
    // GestureRecognizer() noexcept;

    void addGesture(Gesture&& gesture) noexcept;

    absl::optional<int> nextFrame(GestureFrame& frame) noexcept;

    void reset() noexcept;

   private:
    class GestureMatcher {
       public:
        GestureMatcher(Gesture&& gesture) noexcept;

        void reset() noexcept;

        bool matches(GestureFrame& frame) noexcept;

        Gesture& getGesture() noexcept;

       private:
        Gesture gesture;
        long unsigned int next;
    };

    std::list<GestureMatcher> matchers;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_PARSER_H