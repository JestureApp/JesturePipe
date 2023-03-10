#include <iostream>

#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {

class EchoerCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract *cc) {
        for (int i = 0; i < cc->Inputs().NumEntries(); i++) {
            cc->Inputs().Index(i).SetAny();
        }

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        for (int i = 0; i < cc->Inputs().NumEntries(); i++) {
            auto &packet = cc->Inputs().Index(i).Value();

            if (!packet.IsEmpty())
                std::cout << cc->NodeName() << ": Got packet at "
                          << packet.Timestamp() << std::endl;
        }

        return absl::OkStatus();
    }
};

REGISTER_CALCULATOR(EchoerCalculator);

}  // namespace jesturepipe