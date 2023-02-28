
#include "absl/status/status.h"
#include "absl/types/optional.h"
#include "jesturepipe/gesture/gesture.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {
namespace {
const char LandmarksTag[] = "LANDMARKS";
const char FrameTag[] = "FRAME";
}  // namespace

class LandmarkToGestureFrameCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Inputs()
            .Tag(LandmarksTag)
            .Set<absl::optional<mediapipe::NormalizedLandmarkList>>();
        cc->Outputs().Tag(FrameTag).Set<absl::optional<GestureFrame>>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        if (!cc->Inputs().Tag(LandmarksTag).Header().IsEmpty()) {
            cc->Outputs().Tag(FrameTag).SetHeader(
                cc->Inputs().Tag(LandmarksTag).Header());
        }

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        auto landmarks =
            cc->Inputs()
                .Tag(LandmarksTag)
                .Get<absl::optional<mediapipe::NormalizedLandmarkList>>();

        absl::optional<GestureFrame> frame;

        if (landmarks.has_value()) {
            frame = GestureFrame::FromLandmarks(landmarks.value());
        }

        cc->Outputs().Tag(FrameTag).AddPacket(
            mediapipe::MakePacket<absl::optional<GestureFrame>>(frame).At(
                cc->Inputs().Tag(LandmarksTag).Value().Timestamp()));

        return absl::OkStatus();
    }
};

REGISTER_CALCULATOR(LandmarkToGestureFrameCalculator);

}  // namespace jesturepipe