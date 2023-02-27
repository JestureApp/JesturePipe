
#include "absl/status/status.h"
#include "absl/types/optional.h"
#include "jesturepipe/gesture/gesture.h"
#include "jesturepipe/gesture/recognizer.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {
namespace {
const char FrameTag[] = "FRAME";
const char RecognitionTag[] = "REC";
const char GesturesTag[] = "GESTURE";
}  // namespace

class GestureRecognizerCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Inputs().Tag(FrameTag).Set<absl::optional<GestureFrame>>();

        if (cc->Inputs().HasTag(GesturesTag)) {
            cc->Inputs().Tag(GesturesTag).Set<Gesture>();
            cc->SetProcessTimestampBounds(true);
        }

        cc->Outputs().Tag(RecognitionTag).Set<Gesture>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        // Gesture testGesture;

        // testGesture.push_back(GestureFrame(90, 90, 90, 90, 90));

        // recognizer.addGesture(std::move(testGesture));

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        if (cc->Inputs().HasTag(GesturesTag) &&
            !cc->Inputs().Tag(GesturesTag).IsEmpty()) {
            Gesture new_gesture = cc->Inputs().Tag(GesturesTag).Get<Gesture>();
            recognizer.addGesture(std::move(new_gesture));
        }

        if (cc->Inputs().Tag(FrameTag).IsEmpty()) return absl::OkStatus();

        absl::optional<GestureFrame> frame =
            cc->Inputs().Tag(FrameTag).Get<absl::optional<GestureFrame>>();

        if (!frame.has_value()) {
            recognizer.reset();

            return absl::OkStatus();
        }

        absl::optional<Gesture> gesture = recognizer.nextFrame(frame.value());

        if (gesture.has_value()) {
            cc->Outputs()
                .Tag(RecognitionTag)
                .AddPacket(
                    mediapipe::MakePacket<Gesture>(gesture.value())
                        .At(cc->Inputs().Tag(FrameTag).Value().Timestamp()));
        }

        return absl::OkStatus();
    }

   private:
    GestureRecognizer recognizer;
};

REGISTER_CALCULATOR(GestureRecognizerCalculator);

}  // namespace jesturepipe