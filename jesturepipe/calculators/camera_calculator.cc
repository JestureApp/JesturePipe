#include "mediapipe/framework/calculator_framework.h"

class CameraCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) {
        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) {
        return absl::OkStatus();
    }

    absl::Status Close(mediapipe::CalculatorContext* cc) {
        return absl::OkStatus();
    }
};

REGISTER_CALCULATOR(CameraCalculator);