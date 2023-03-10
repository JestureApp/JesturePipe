#include "jesturepipe/gesture/library.h"

namespace jesturepipe {

std::shared_lock<std::shared_mutex> GestureLibrary::RLock() {
    return std::shared_lock<std::shared_mutex>(mutex);
}

std::unique_lock<std::shared_mutex> GestureLibrary::WLock() {
    return std::unique_lock<std::shared_mutex>(mutex);
}

void GestureLibrary::Set(int id, Gesture&& gesture) {
    auto lk = WLock();

    gestures.insert_or_assign(id, std::move(gesture));
}

void GestureLibrary::Remove(int id) {
    auto lk = WLock();

    gestures.erase(id);
}

absl::optional<Gesture> GestureLibrary::Get(int id) {
    auto lk = RLock();
    absl::optional<Gesture> gesture;

    auto result = gestures.find(id);

    if (result != gestures.end()) {
        gesture = result->second;
    }

    return gesture;
}

absl::flat_hash_map<int, Gesture>::iterator GestureLibrary::begin() {
    return gestures.begin();
}

absl::flat_hash_map<int, Gesture>::iterator GestureLibrary::end() {
    return gestures.end();
}

}  // namespace jesturepipe