#include "absl/time/time.h"
namespace jesturepipe {
class FrameCount {
    public:
      int slide_left_count;
      int slide_right_count;
      bool should_cool_down = false;
      absl::Time cool_down_init_time;
      static FrameCount& get_instance();
    };
}
