#include <iostream>

#include "actions/actions.h"
#include "jesturepipe/actions/mapper.h"
#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {

namespace api2 = mediapipe::api2;

class ActionDispatcherCalculator : public api2::Node {
   public:
    static constexpr api2::SideInput<std::shared_ptr<ActionMapper>> kMapper{
        "MAPPER"};

    static constexpr api2::Input<int> kGestureId{"GESTURE_ID"};

    MEDIAPIPE_NODE_CONTRACT(kMapper, kGestureId)

    ActionDispatcherCalculator()
        : actions(actions::Actions::Create().value()) {}

    absl::Status Open(mediapipe::CalculatorContext *cc) override {
        mapper = *kMapper(cc);

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        std::shared_lock<std::shared_mutex> lk(mapper->mutex);

        int gesture_id = *kGestureId(cc);

        if (mapper->mapping.contains(gesture_id)) {
            auto action = mapper->mapping[gesture_id];

            actions.Perform(action, actions::action::target::Focused{})
                .get()
                .IgnoreError();
        }

        return absl::OkStatus();
    }

   private:
    actions::Actions actions;
    std::shared_ptr<ActionMapper> mapper;
};

MEDIAPIPE_REGISTER_NODE(ActionDispatcherCalculator);

}  // namespace jesturepipe