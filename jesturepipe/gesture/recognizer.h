#ifndef JESTUREPIPE_GESTURE_RECOGNIZER_H
#define JESTUREPIPE_GESTURE_RECOGNIZER_H

#include <list>

#include "absl/types/optional.h"
#include "jesturepipe/gesture/gesture.h"
#include "jesturepipe/gesture/library.h"

namespace jesturepipe {

class GestureRecognizer {
   public:
    GestureRecognizer() = delete;
    GestureRecognizer(std::shared_ptr<GestureLibrary> library,
                      double threshold);

    GestureRecognizer(GestureRecognizer&) = delete;
    GestureRecognizer& operator=(GestureRecognizer&) = delete;

    GestureRecognizer(GestureRecognizer&&) = delete;
    GestureRecognizer& operator=(GestureRecognizer&&) = delete;

    /// \brief Processes the next frame and attempts to match it against
    /// known gestures.
    absl::optional<int> ProcessFrame(const GestureFrame& frame);

   private:
    class GestureMatcher {
       public:
        GestureMatcher(int id, Gesture gesture, GestureFrame::Comparator* comp);

        bool Advance(const GestureFrame& frame);

        absl::optional<int> Matches();

       private:
        int at;
        int id;
        Gesture gesture;
        GestureFrame::Comparator* comp;
    };

    std::shared_ptr<GestureLibrary> library;
    GestureFrame::Comparator comp;
    std::list<GestureMatcher> matchers;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_RECOGNIZER_H