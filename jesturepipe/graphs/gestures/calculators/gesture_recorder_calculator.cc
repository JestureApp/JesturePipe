#include <iostream>

#include "jesturepipe/gesture/gesture.h"
#include "jesturepipe/gesture/recorder.h"
#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {
namespace api2 = mediapipe::api2;

class GestureRecorderCalculator : public api2::Node {
   public:
    static constexpr api2::Input<GestureFrame> kFrame{"GESTURE_FRAME"};
    static constexpr api2::Input<api2::AnyType> kRecReset{"REC_RESET"};

    static constexpr api2::Output<Gesture> kGesture{"GESTURE"};

    MEDIAPIPE_NODE_CONTRACT(kFrame, kRecReset, kGesture)

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        if (!kRecReset(cc).IsEmpty()) {
            Gesture gesture = recorder.Finish();
            std::cout << "num frames: " << gesture.frames->size() << std::endl;
            if (gesture.frames->size() > 0) {
                kGesture(cc).Send(gesture, cc->InputTimestamp());
            }

            recorder = GestureRecorder();
            return absl::OkStatus();
        }

        if (kFrame(cc).IsEmpty()) return absl::OkStatus();

        recorder.AddFrame(*kFrame(cc));

        return absl::OkStatus();
    }

   private:
    GestureRecorder recorder;
};

MEDIAPIPE_REGISTER_NODE(GestureRecorderCalculator);

}  // namespace jesturepipe