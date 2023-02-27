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
        std::cout << "Echoer got input at "
                  << cc->Inputs().Index(0).Value().Timestamp() << std::endl;

        return absl::OkStatus();
    }
};

REGISTER_CALCULATOR(EchoerCalculator);

}  // namespace jesturepipe