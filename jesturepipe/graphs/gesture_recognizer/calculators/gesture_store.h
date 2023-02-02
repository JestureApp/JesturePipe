#ifndef __H_GESTURE_STORE__
#define __H_GESTURE_STORE__

#include "jesturepipe/graphs/gesture_recognizer/calculators/gesture.h"
#include <mutex>
#include <vector>
#include <unistd.h>

namespace jesturepipe {
class GestureStore {
    // private:
    //     GestureStore() = default;

    public:
        bool to_record;
        bool finished_custom_gesture;
        time_t start_time;
        std::vector<GestureFeature> features;
        GestureFeature final_feature;
        static GestureStore& get_instance();
       
    };
}
#endif /* __H_GESTURE_STORE__ */
