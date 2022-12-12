
#include "absl/status/status.h"
#include "jesturepipe/calculators/hand_landmark_lite.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/util/tflite/tflite_model_loader.h"
#include "tensorflow/lite/model.h"

namespace jesturepipe {

namespace {
constexpr char ModelTag[] = "MODEL";
}

class HandLandmarkModelLiteCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->OutputSidePackets().Tag(ModelTag).Set<mediapipe::TfLiteModelPtr>();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        std::unique_ptr<tflite::FlatBufferModel> model =
            tflite::FlatBufferModel::BuildFromBuffer(
                reinterpret_cast<const char*>(HAND_LANDMARK_LITE_MODEL),
                HAND_LANDMARK_LITE_MODEL_len);

        if (!model) {
            return absl::InternalError("Failed to load model");
        }

        cc->OutputSidePackets().Tag(ModelTag).Set(
            mediapipe::MakePacket<mediapipe::TfLiteModelPtr>(
                model.release(),
                [](tflite::FlatBufferModel* model) { delete model; }));

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        return absl::OkStatus();
    }
};

REGISTER_CALCULATOR(HandLandmarkModelLiteCalculator);

}  // namespace jesturepipe