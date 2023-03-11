#ifndef JESTUREPIPE_GESTURE_LIBRARY_H
#define JESTUREPIPE_GESTURE_LIBRARY_H

#include <map>
#include <mutex>
#include <shared_mutex>

#include "absl/container/flat_hash_map.h"
#include "absl/types/optional.h"
#include "jesturepipe/gesture/gesture.h"

namespace jesturepipe {

/// \brief A thread safe library of gestures
class GestureLibrary {
   public:
    GestureLibrary() = default;

    void Set(int id, Gesture&& gesture);
    void Remove(int id);

    absl::optional<Gesture> Get(int id);

    std::shared_lock<std::shared_mutex> RLock();
    std::unique_lock<std::shared_mutex> WLock();

    // Must acquire read lock before iterating
    absl::flat_hash_map<int, Gesture>::iterator begin();
    absl::flat_hash_map<int, Gesture>::iterator end();

   private:
    std::shared_mutex mutex;
    absl::flat_hash_map<int, Gesture> gestures;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_GESTURE_LIBRARY_H