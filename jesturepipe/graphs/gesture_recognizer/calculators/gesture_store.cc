#include "jesturepipe/graphs/gesture_recognizer/calculators/gesture_store.h"

#include <pthread.h>

#include <mutex>
#include <vector>
namespace jesturepipe {
// class GestureStore {

// private:
// GestureStore::GestureStore() noexcept = default;

// public:
// bool to_record;
// std::vector<GestureFeature> features;
// GestureFeature feature;

GestureStore& GestureStore::get_instance() {
    static GestureStore instance;
    return instance;
}
// }
};  // namespace jesturepipe
