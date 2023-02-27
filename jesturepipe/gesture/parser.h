#ifndef JESTUREPIPE_GESTURE_PARSER_H
#define JESTUREPIPE_GESTURE_PARSER_H

#include "absl/container/flat_hash_map.h"
#include "absl/types/optional.h"
#include "absl/types/variant.h"
#include "jesturepipe/gesture/gesture.h"

namespace jesturepipe {

namespace {
typedef struct {
} Terminal;
}  // namespace

class GestureParser {
   public:
    GestureParser() noexcept;

    void AddGesture(Gesture gesture) noexcept;

    void consumeFrame(Gesture::KeyFrame frame) noexcept;

    absl::optional<Gesture> terminateGesture() noexcept;

   private:
    absl::flat_hash_map<Gesture::KeyFrame, int> frame_ids;
    absl::flat_hash_map<int, absl::variant<int, Gesture>> state_map;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_PARSER_H