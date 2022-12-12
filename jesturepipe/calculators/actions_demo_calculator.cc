#include "absl/status/status.h"
#include "actions/actions.h"
#include "jesturepipe/graphs/gesture_recognizer/calculators/gesture.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {
namespace {
const char GestureTag[] = "GESTURE";
}

class ActionsDemoCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Inputs().Tag(GestureTag).Set<Gesture>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        auto maybe_actions = actions::Actions<int>::Create();

        if (!maybe_actions.ok()) {
            return maybe_actions.status();
        }

        actions = maybe_actions.value();

        actions->Add(0, actions::Keystrokes{
                            {'P', 0},
                            {'e', 0},
                            {'a', 0},
                            {'c', 0},
                            {'e', 0},
                            {' ', 0},
                        });

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        auto gesture = cc->Inputs().Tag(GestureTag).Get<Gesture>();

        if (gesture == Gesture::Peace) {
            return actions->Perform(0);
        }

        return absl::OkStatus();
    }

   private:
    std::shared_ptr<actions::Actions<int>> actions;
};

REGISTER_CALCULATOR(ActionsDemoCalculator);
}  // namespace jesturepipe