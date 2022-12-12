#include "mediapipe/framework/calculator_framework.h"

const char VideoOutputStream[] = "VIDEO";
const char CameraInputPacket[] = "CAMERA";

// TODO: docs

namespace jesturepipe {
// Example:
// node {
//  calculator: "CameraCalculator"
//  input_side_packet: "CAMERA:camera"
//  output_stream: "VIDEO:video"
// }
class CameraCalculator : public mediapipe::CalculatorBase {
public:
  static absl::Status GetContract(mediapipe::CalculatorContract *cc) {
    return absl::OkStatus();
  }

  absl::Status Open(mediapipe::CalculatorContext *cc) {
    return absl::OkStatus();
  }

  absl::Status Process(mediapipe::CalculatorContext *cc) {
    return absl::OkStatus();
  }

  absl::Status Close(mediapipe::CalculatorContext *cc) {
    return absl::OkStatus();
  }
};

REGISTER_CALCULATOR(CameraCalculator);
} // namespace jesturepipe