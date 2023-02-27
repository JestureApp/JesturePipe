#ifndef JESTUREPIPE_GESTURE_GESTURE_H
#define JESTUREPIPE_GESTURE_GESTURE_H

#include <functional>

#include "absl/hash/hash.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {
class Gesture {
   public:
    /**
     * An important frame in the gesture. This may or may not end up equating to
     * multiple camera frames.
     *
     * Used to represent the general shape of the hand at a point in time.
     */
    class KeyFrame {
       public:
        /**
         * Constructs a new key frame from a list of hand landmarks.
         */
        static KeyFrame FromLandmarks(
            mediapipe::NormalizedLandmarkList& landmarks) noexcept;

        bool operator=(KeyFrame& other) noexcept;

        template <typename H>
        friend H AbslHashValue(H h, const KeyFrame& frame) {
            // TODO
            return H::combine(0);
        }

       private:
        typedef enum { Left, Right, Up, Down } Direction;

        KeyFrame() noexcept;
    };

    void AddFrame(KeyFrame frame) noexcept;
    void AddFrame(mediapipe::NormalizedLandmarkList& landmarks) noexcept;

    KeyFrame& operator[](int index) noexcept;

   private:
    std::vector<KeyFrame> frames;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_GESTURE_H