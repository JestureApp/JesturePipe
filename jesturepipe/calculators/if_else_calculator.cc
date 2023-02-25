#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/util/header_util.h"

const char IfStream[] = "IF";
const char ElseStream[] = "ELSE";
const char ConditionStream[] = "COND";
const char ValueStream[] = "VALUE";

namespace jesturepipe {
// Example:
// node {
//  calculator: "CameraCalculator"
//  input_side_packet: "CAMERA:camera"
//  output_stream: "VIDEO:video"
// }
class IfElseCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        // cc->Outputs().Tag(VideoOutputStream).Set<mediapipe::ImageFrame>();
        // cc->InputSidePackets().Tag(CameraInputPacket).Set<int>();

        cc->InputSidePackets().Tag(IfStream).SetAny();
        cc->InputSidePackets()
            .Tag(ElseStream)
            .SetSameAs(&cc->InputSidePackets().Tag(IfStream));
        cc->InputSidePackets().Tag(ConditionStream).Set<int>();

        cc->OutputSidePackets()
            .Tag(ValueStream)
            .SetSameAs(&cc->InputSidePackets().Tag(IfStream));

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        int cond = cc->InputSidePackets().Tag(ConditionStream).Get<int>();

        RET_CHECK_OK(CopyInputHeadersToOutputs(cc->Inputs(), &cc->Outputs()));

        if (cond) {
            auto packet = cc->InputSidePackets().Tag(IfStream);

            cc->OutputSidePackets().Tag(ValueStream).Set(packet);
        } else {
            auto packet = cc->InputSidePackets().Tag(ElseStream);

            cc->OutputSidePackets().Tag(ValueStream).Set(packet);
        }

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        return absl::OkStatus();
    }
};

REGISTER_CALCULATOR(IfElseCalculator);
}  // namespace jesturepipe