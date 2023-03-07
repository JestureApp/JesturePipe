#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/util/header_util.h"

namespace jesturepipe {

class EchoerCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Inputs().Index(0).SetAny();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        auto& input = cc->Inputs().Index(0);

        if (input.IsEmpty()) return absl::OkStatus();

        mediapipe::TypeId type_id = input.Value().GetTypeId();

        std::cout << cc->NodeName() << ": Echoer got packet at "
                  << input.Value().Timestamp();

        if (type_id == mediapipe::kTypeId<bool>) {
            std::cout << " with value " << input.Get<bool>();
        }

        std::cout << std::endl;

        return absl::OkStatus();
    }
};

REGISTER_CALCULATOR(EchoerCalculator);

}  // namespace jesturepipe