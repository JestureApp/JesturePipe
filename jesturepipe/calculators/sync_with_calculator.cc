#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/util/header_util.h"

namespace jesturepipe {

namespace {
const char SyncTag[] = "SYNC";
}

class SyncWithCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->SetProcessTimestampBounds(true);

        cc->Inputs().Tag(SyncTag).SetAny();
        cc->Inputs().Index(0).SetAny();

        cc->Outputs().Index(0).SetSameAs(&cc->Inputs().Index(0));

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        auto& input = cc->Inputs().Index(0);
        auto& output = cc->Outputs().Index(0);

        if (!input.Header().IsEmpty()) output.SetHeader(input.Header());

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        auto& sync = cc->Inputs().Tag(SyncTag);
        auto& input = cc->Inputs().Index(0);
        auto& output = cc->Outputs().Index(0);

        if (sync.IsEmpty()) {
            std::cout << cc->NodeName() << ": sync empty" << std::endl;

            output.SetNextTimestampBound(
                cc->InputTimestamp().NextAllowedInStream());
            return absl::OkStatus();
        }

        if (input.IsEmpty()) {
            std::cout << cc->NodeName()
                      << ": input empty. Advancing timestamp bound"
                      << std::endl;
            output.SetNextTimestampBound(sync.Value().Timestamp() + 1);
            return absl::OkStatus();
        }

        output.AddPacket(input.Value().At(sync.Value().Timestamp()));

        return absl::OkStatus();
    }
};

REGISTER_CALCULATOR(SyncWithCalculator);

}  // namespace jesturepipe