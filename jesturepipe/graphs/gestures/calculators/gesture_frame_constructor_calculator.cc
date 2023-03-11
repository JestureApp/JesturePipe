#include <iostream>

#include "absl/time/time.h"
#include "absl/types/optional.h"
#include "jesturepipe/gesture/frame_constructor.h"
#include "jesturepipe/gesture/gesture.h"
#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {

namespace api2 = mediapipe::api2;

class GestureFrameConstructorCalculator : public api2::Node {
   public:
    static constexpr api2::SideInput<double> kThresh{"THRESH"};

    static constexpr api2::Input<mediapipe::NormalizedLandmarkList> kLandmarks{
        "LANDMARKS"};

    static constexpr api2::Input<absl::Time> kTimes{"TIMES"};

    static constexpr api2::Output<GestureFrame> kGestureFrame{"GESTURE_FRAME"};

    MEDIAPIPE_NODE_CONTRACT(kThresh, kLandmarks, kTimes, kGestureFrame)

    static absl::Status UpdateContract(mediapipe::CalculatorContract *cc) {
        cc->SetProcessTimestampBounds(true);
        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext *cc) override {
        cc->SetOffset(mediapipe::TimestampDiff(0));

        frame_constructor = GestureFrameConstructor(*kThresh(cc));

        return absl::OkStatus();
    }

    // CHECKME: Do I need to update output timestamp bounds
    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        if (kLandmarks(cc).IsEmpty()) {
            // std::cout << cc->NodeName() << ": Reset at " <<
            // cc->InputTimestamp()
            //           << std::endl;
            frame_constructor.Reset();
            return absl::OkStatus();
        }

        mediapipe::NormalizedLandmarkList landmarks = *kLandmarks(cc);
        absl::Time time = *kTimes(cc);

        absl::optional<GestureFrame> frame =
            frame_constructor.OnLandmarks(*kLandmarks(cc), time);

        if (frame.has_value())
            kGestureFrame(cc).Send(std::move(frame.value()),
                                   cc->InputTimestamp());

        return absl::OkStatus();
    }

   private:
    GestureFrameConstructor frame_constructor;
};

MEDIAPIPE_REGISTER_NODE(GestureFrameConstructorCalculator);

}  // namespace jesturepipe