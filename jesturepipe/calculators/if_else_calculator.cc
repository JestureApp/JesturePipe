#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/util/header_util.h"

namespace jesturepipe {

namespace api2 = mediapipe::api2;

// Example
// node {
//     calculator: "IfElseCalculator"
//     input_side_packet: "COND:if_cond"
//     input_side_packet: "IF:on_true"
//     input_side_packet: "ELSE:on_false"
//     output_side_packet: "VALUE:result"
// }
class IfElseCalculator : public api2::Node {
   public:
    static constexpr api2::SideInput<bool> kCond{"COND"};
    static constexpr api2::SideInput<api2::AnyType> kIf{"IF"};
    static constexpr api2::SideInput<api2::SameType<kIf>> kElse{"ELSE"};

    static constexpr api2::SideOutput<api2::SameType<kIf>> kValue{"VALUE"};

    MEDIAPIPE_NODE_CONTRACT(kCond, kIf, kElse, kValue)

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        RET_CHECK_OK(CopyInputHeadersToOutputs(cc->Inputs(), &cc->Outputs()));

        if (*kCond(cc)) {
            kValue(cc).Set(kIf(cc));
        } else {
            kValue(cc).Set(kElse(cc));
        }

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        return absl::OkStatus();
    }
};

MEDIAPIPE_REGISTER_NODE(IfElseCalculator);

}  // namespace jesturepipe