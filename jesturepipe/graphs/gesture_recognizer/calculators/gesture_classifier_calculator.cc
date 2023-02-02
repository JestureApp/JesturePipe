#include <tuple>
#include <vector>

#include "absl/status/status.h"
#include "jesturepipe/graphs/gesture_recognizer/calculators/gesture.h"
#include "jesturepipe/graphs/gesture_recognizer/calculators/gesture_store.h"
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

        GestureStore& instance = GestureStore::get_instance();
        if (!instance.to_record && instance.finished_custom_gesture) {
            if (instance.features.size() != 0) {
                GestureFeature custom_feature = instance.final_feature;
                // Custom Gesture
                if (feature.index_vertical == custom_feature.index_vertical &&
                    feature.middle_vertical == custom_feature.middle_vertical &&
                    feature.ring_vertical == custom_feature.ring_vertical &&
                    feature.pinky_vertical == custom_feature.pinky_vertical &&
                    feature.thumb_vertical == custom_feature.thumb_vertical &&
                    feature.index_horizontal ==
                        custom_feature.index_horizontal &&
                    feature.middle_horizontal ==
                        custom_feature.middle_horizontal &&
                    feature.ring_horizontal == custom_feature.ring_horizontal &&
                    feature.pinky_horizontal ==
                        custom_feature.pinky_horizontal &&
                    feature.thumb_horizontal ==
                        custom_feature.thumb_horizontal) {
                    gesture = Gesture::Custom;
                    std::cout << "Saw Custom Gesture" << std::endl;
                }
            } else {
                // Stop
                if (feature.index_vertical == FingerDirection::Up &&
                    feature.middle_vertical == FingerDirection::Up &&
                    feature.ring_vertical == FingerDirection::Up &&
                    feature.pinky_vertical == FingerDirection::Up &&
                    feature.thumb_vertical == FingerDirection::Up &&
                    feature.thumb_horizontal == FingerDirection::Left &&
                    feature.middle_angle < 110 && feature.middle_angle > 60) {
                    gesture = Gesture::Stop;

                    std::cout << "Saw Stop Gesture" << std::endl;
                }
                // Pause
                else if (feature.index_vertical == FingerDirection::Up &&
                         feature.middle_vertical == FingerDirection::Up &&
                         feature.ring_vertical == FingerDirection::Down &&
                         feature.pinky_vertical == FingerDirection::Down &&
                         feature.middle_angle < 120 &&
                         feature.middle_angle > 60) {
                    gesture = Gesture::Pause;

                    std::cout << "Saw Pause Gesture" << std::endl;
                }
                // Okay
                else if (feature.index_vertical == FingerDirection::Down &&
                         feature.middle_vertical == FingerDirection::Up &&
                         feature.ring_vertical == FingerDirection::Up &&
                         feature.pinky_vertical == FingerDirection::Up) {
                    gesture = Gesture::Okay;

                    std::cout << "Saw Okay Gesture" << std::endl;
                }
                // Previous
                else if (feature.index_horizontal == FingerDirection::Left &&
                         feature.middle_horizontal == FingerDirection::Right &&
                         feature.ring_horizontal == FingerDirection::Right &&
                         feature.pinky_horizontal == FingerDirection::Right &&
                         feature.thumb_vertical == FingerDirection::Up &&
                         feature.thumb_index_vertical == FingerDirection::Up) {
                    gesture = Gesture::Previous;

                    std::cout << "Saw Previous Gesture" << std::endl;
                }
                // Next
                else if (feature.index_horizontal == FingerDirection::Right &&
                         feature.middle_horizontal == FingerDirection::Left &&
                         feature.ring_horizontal == FingerDirection::Left &&
                         feature.pinky_horizontal == FingerDirection::Left &&
                         feature.thumb_vertical == FingerDirection::Up &&
                         feature.thumb_index_vertical == FingerDirection::Up) {
                    gesture = Gesture::Next;

                    std::cout << "Saw Next Gesture" << std::endl;
                } else {
                    gesture = Gesture::Unknown;
                    std::cout << "Unkown Gesture" << std::endl;
                    std::cout << std::endl;
                }
            }
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