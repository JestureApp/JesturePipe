#ifndef JESTUREPIPE_CALCULATORS_FIXED_LENGTH_VECTOR_CALCULATOR_H
#define JESTUREPIPE_CALCULATORS_FIXED_LENGTH_VECTOR_CALCULATOR_H

#include "absl/status/status.h"
#include "absl/types/optional.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {

namespace {
const char LengthTag[] = "LENGTH";
const char TickTag[] = "TICK";
const char VectorTag[] = "VECTOR";
}  // namespace

template <typename T>
class FixedLengthVectorCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->SetProcessTimestampBounds(true);

        cc->InputSidePackets().Tag(LengthTag).Set<int>();
        cc->Inputs().Tag(TickTag).SetAny();
        cc->Inputs().Tag(VectorTag).Set<std::vector<T>>();

        cc->Outputs().Index(0).Set<std::vector<absl::optional<T>>>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        length = cc->InputSidePackets().Tag(LengthTag).Get<int>();

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        if (cc->Inputs().Tag(TickTag).IsEmpty()) return absl::OkStatus();

        std::vector<absl::optional<T>> output(length);

        if (!cc->Inputs().Tag(VectorTag).IsEmpty()) {
            std::vector<T> vec =
                cc->Inputs().Tag(VectorTag).Get<std::vector<T>>();

            for (unsigned long i = 0; i < std::min(vec.size(), output.size());
                 i++)
                output[i] = vec[i];
        }

        cc->Outputs().Index(0).AddPacket(
            mediapipe::MakePacket<std::vector<absl::optional<T>>>(output).At(
                cc->Inputs().Tag(TickTag).Value().Timestamp()));

        return absl::OkStatus();
    }

   private:
    int length = 0;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_CALCULATORS_OPTIONAL_CALCULATOR_H