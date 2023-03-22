#include "jesturepipe/gesture/frame_count.h"
#include <mutex>
#include <pthread.h>
namespace jesturepipe {
    FrameCount& FrameCount::get_instance(){
        pthread_mutex_t mutex;
        pthread_mutex_lock(&mutex);
        static FrameCount instance;
        pthread_mutex_unlock(&mutex);
        return instance;
    }
};
