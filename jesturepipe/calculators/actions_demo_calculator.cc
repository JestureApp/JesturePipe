#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"
#include "actions/actions.h"

namespace jesturepipe {
  class ActionsDemoCalculator : public mediapipe::CalculatorBase {
    public:
      static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Inputs().Index(0).SetAny();

        return absl::OkStatus();
      }

      absl::Status Open(mediapipe::CalculatorContext* cc) override {
        auto maybe_actions = actions::Actions<int>::Create();

        if (! maybe_actions.ok()) {
          return maybe_actions.status();
        }

        actions = maybe_actions.value();

        actions->Add(0, actions::Keystrokes{{'I', 0}, {'t', 0}, {' ', 0}, {'w', 0}, {'o', 0}, {'r', 0}, {'k', 0}, {'s', 0}, {' ', 0}, });

        return absl::OkStatus();
      }

      absl::Status Process(mediapipe::CalculatorContext* cc) override{
        return actions->Perform(0);
        // return absl::OkStatus();
      }

    private:
        std::shared_ptr<actions::Actions<int>> actions;
  };

  REGISTER_CALCULATOR(ActionsDemoCalculator);
}