#include "absl/types/optional.h"
#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {

namespace api2 = mediapipe::api2;

class StateChangeCalculator : public api2::Node {
   public:
    static constexpr api2::Input<bool> kState{"STATE"};
    static constexpr api2::Output<mediapipe::Timestamp> kChange{"STATE_CHANGE"};

    MEDIAPIPE_NODE_CONTRACT(kState, kChange)

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        if (!last_state.has_value()) {
            last_state = *kState(cc);
            return absl::OkStatus();
        }

        bool last = last_state.value();

        if (last != *kState(cc)) {
            auto ts = cc->InputTimestamp();

            kChange(cc).Send(ts, ts);

            last_state = *kState(cc);
        }

        return absl::OkStatus();
    }

   private:
    absl::optional<bool> last_state;
};

MEDIAPIPE_REGISTER_NODE(StateChangeCalculator);

}  // namespace jesturepipe