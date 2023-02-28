#include "absl/status/status.h"
#include "absl/types/optional.h"
#include "jesturepipe/gesture/gesture.h"
#include "jesturepipe/gesture/recorder.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {

namespace {
const char FrameTag[] = "FRAME";
const char FinishTag[] = "FINISH";
const char GestureTag[] = "GESTURE";
}  // namespace

class GestureRecorderCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->SetProcessTimestampBounds(true);
        cc->Inputs().Tag(FrameTag).Set<absl::optional<GestureFrame>>();
        cc->Inputs().Tag(FinishTag).SetAny();

        cc->Outputs().Tag(GestureTag).Set<Gesture>();

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        auto& input = cc->Inputs().Tag(FrameTag);
        auto& finish = cc->Inputs().Tag(FinishTag);
        auto& output = cc->Outputs().Tag(GestureTag);

        if (!finish.IsEmpty()) {
            std::cout << "Finished recording gesture" << std::endl;
            Gesture gesture = recorder.finish();

            if (gesture.frames.size()) {
                output.AddPacket(mediapipe::MakePacket<Gesture>(gesture).At(
                    input.Value().Timestamp()));
                return absl::OkStatus();
            }
        }

        if (!input.IsEmpty() &&
            input.Get<absl::optional<GestureFrame>>().has_value()) {
            std::cout << "Recorded Frame" << std::endl;

            GestureFrame frame =
                input.Get<absl::optional<GestureFrame>>().value();

            recorder.addFrame(frame);
        }

        output.SetNextTimestampBound(
            cc->InputTimestamp().NextAllowedInStream());

        return absl::OkStatus();
    }

   private:
    GestureRecorder recorder;
};

REGISTER_CALCULATOR(GestureRecorderCalculator);

}  // namespace jesturepipe