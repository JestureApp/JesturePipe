#include "absl/status/status.h"
#include "jesturepipe/graphs/gesture_recognizer/calculators/gesture.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {

namespace {
const char GestureFeatureTag[] = "GESTURE_FEATURE";
const char GestureTag[] = "GESTURE";
}  // namespace

const char* FingerDirectionToString(FingerDirection direction) {
    switch (direction) {
        case Left:
            return "Left";
        case Right:
            return "Right";
        case Up:
            return "Up";
        case Down:
            return "Down";
        default:
            return "Unknown";
    }
}

class GestureClassifierCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Inputs().Tag(GestureFeatureTag).Set<GestureFeature>();
        cc->Outputs().Tag(GestureTag).Set<Gesture>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        auto feature =
            cc->Inputs().Tag(GestureFeatureTag).Get<GestureFeature>();

        Gesture gesture;

        if (feature.index == FingerDirection::Up &&
            feature.middle == FingerDirection::Up &&
            feature.ring == FingerDirection::Down &&
            feature.pinky == FingerDirection::Down &&
            feature.thumb == FingerDirection::Up) {
            gesture = Gesture::Peace;

            std::cout << "Saw Peace Gesture" << std::endl;

        } else {
            gesture = Gesture::Unknown;

            std::cout << "Unkown Gesture" << std::endl;
            std::cout << "Index: " << FingerDirectionToString(feature.index)
                      << std::endl;

            std::cout << "Middle: " << FingerDirectionToString(feature.middle)
                      << std::endl;

            std::cout << "Ring: " << FingerDirectionToString(feature.ring)
                      << std::endl;

            std::cout << "Pinky: " << FingerDirectionToString(feature.pinky)
                      << std::endl;

            std::cout << "Thumb: " << FingerDirectionToString(feature.thumb)
                      << std::endl;

            std::cout << std::endl;
        }

        cc->Outputs()
            .Tag(GestureTag)
            .AddPacket(mediapipe::MakePacket<Gesture>(gesture).At(
                cc->InputTimestamp()));

        return absl::OkStatus();
    }
};

REGISTER_CALCULATOR(GestureClassifierCalculator);

}  // namespace jesturepipe