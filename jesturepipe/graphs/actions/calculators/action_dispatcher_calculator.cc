#include <iostream>

#include "actions/actions.h"
#include "jesturepipe/actions/mapper.h"
#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {

namespace api2 = mediapipe::api2;

class ActionDispatcherCalculator : public api2::Node {
   public:
    static constexpr api2::SideInput<std::shared_ptr<ActionMapper>> kMapper{
        "MAPPER"};

    static constexpr api2::Input<int> kGestureId{"GESTURE_ID"};
    static constexpr api2::Input<mediapipe::NormalizedLandmarkList> kLandmarks{
        "LANDMARKS"};

    MEDIAPIPE_NODE_CONTRACT(kMapper, kGestureId, kLandmarks)

    ActionDispatcherCalculator()
        : actions(actions::Actions::Create().value()) {}

    absl::Status Open(mediapipe::CalculatorContext *cc) override {
        mapper = *kMapper(cc);

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        std::shared_lock<std::shared_mutex> lk(mapper->mutex);

        if (!kGestureId(cc).IsEmpty() &&
            mapper->mapping.contains(*kGestureId(cc))) {
            auto gesture_id = *kGestureId(cc);
            auto action = mapper->mapping[gesture_id];

            if (action.cursor_control == CursorControl::Grab ||
                (action.cursor_control == CursorControl::Toggle &&
                 !cursor_tracking)) {
                LOG(INFO) << "Grabbing cursor";

                init_tracking = true;
                cursor_tracking = true;
            } else if (action.cursor_control == CursorControl::Release ||
                       (action.cursor_control == CursorControl::Toggle &&
                        cursor_tracking)) {
                LOG(INFO) << "Releasing cursor";

                cursor_tracking = false;
            }

            LOG(INFO) << "Performing action for gesture " << gesture_id;

            return actions
                .Perform(action.type, actions::action::target::Focused{})
                .get();
        }

        if (cursor_tracking && !kLandmarks(cc).IsEmpty()) {
            auto landmark = kLandmarks(cc)->landmark();

            double hand_x = landmark[0].x();
            double hand_y = landmark[0].y();

            double x = 0;
            double y = 0;

            if (!init_tracking) {
                x = hand_x - last_position.first;
                y = hand_y - last_position.second;
            } else {
                init_tracking = false;
            }

            last_position = {hand_x, hand_y};

            auto status = actions
                              .Perform(
                                  actions::action::CursorMove{
                                      .x = x, .y = y, .relative = true},
                                  actions::action::target::Focused{})
                              .get();

            if (!status.ok()) return status;
        }

        return absl::OkStatus();
    }

   private:
    std::pair<double, double> last_position = {0, 0};
    bool cursor_tracking = false;
    bool init_tracking = false;
    actions::Actions actions;
    std::shared_ptr<ActionMapper> mapper;
};

MEDIAPIPE_REGISTER_NODE(ActionDispatcherCalculator);

}  // namespace jesturepipe