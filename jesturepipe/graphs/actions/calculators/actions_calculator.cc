#include "absl/status/status.h"
#include "actions/action.h"
#include "actions/actions.h"
#include "jesturepipe/graphs/gesture_recognizer/calculators/gesture.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {

namespace {
using namespace actions;
const char GestureTag[] = "GESTURE";
}  // namespace

class ActionsCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Inputs().Tag(GestureTag).Set<Gesture>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        auto maybe_actions = Actions::Create();

        if (!maybe_actions.ok()) return maybe_actions.status();

        actions = std::make_unique<Actions>(std::move(maybe_actions.value()));

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        auto gesture = cc->Inputs().Tag(GestureTag).Get<Gesture>();

        if (gesture == Gesture::Peace) {
            auto keystroke = action::ParseKeystroke("super+enter");

            if (!keystroke.ok()) return keystroke.status();

            return actions
                ->Perform(keystroke.value(), action::target::Focused())
                .get();
        }

        return absl::OkStatus();
    }

   private:
    std::unique_ptr<Actions> actions;
};

REGISTER_CALCULATOR(ActionsCalculator);

}  // namespace jesturepipe