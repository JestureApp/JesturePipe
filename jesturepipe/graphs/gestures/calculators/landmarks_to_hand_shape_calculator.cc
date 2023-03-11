#include "jesturepipe/gesture/gesture.h"
#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {

namespace api2 = mediapipe::api2;

class LandmarksToHandShapeCalculator : public api2::Node {
   public:
    static constexpr api2::Input<mediapipe::NormalizedLandmarkList> kLandmarks{
        "LANDMARKS"};

    static constexpr api2::Output<HandShape> kHandShape{"HAND_SHAPE"};

    MEDIAPIPE_NODE_CONTRACT(kLandmarks, kHandShape);

    absl::Status Open(mediapipe::CalculatorContext *cc) override {
        cc->SetOffset(mediapipe::TimestampDiff(0));
        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        HandShape hand_shape = HandShape::FromLandmarks(*kLandmarks(cc));

        kHandShape(cc).Send(hand_shape, cc->InputTimestamp());

        return absl::OkStatus();
    }
};

MEDIAPIPE_REGISTER_NODE(LandmarksToHandShapeCalculator);

}  // namespace jesturepipe