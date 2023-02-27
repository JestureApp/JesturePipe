#ifndef JESTUREPIPE_CALCULATORS_OPTIONAL_CALCULATOR_H
#define JESTUREPIPE_CALCULATORS_OPTIONAL_CALCULATOR_H

#include "absl/status/status.h"
#include "absl/types/optional.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {

namespace {
const char TickTag[] = "TICK";
const char OptionalTag[] = "OPTIONAL";
}  // namespace

template <typename T>
class OptionalCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->SetProcessTimestampBounds(true);

        cc->Inputs().Tag(TickTag).SetAny();
        cc->Inputs().Tag(OptionalTag).Set<T>();

        cc->Outputs().Index(0).Set<absl::optional<T>>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        if (cc->Inputs().Tag(TickTag).IsEmpty()) return absl::OkStatus();

        absl::optional<T> output;

        if (!cc->Inputs().Tag(OptionalTag).IsEmpty()) {
            output = cc->Inputs().Tag(OptionalTag).Get<T>();
        }

        cc->Outputs().Index(0).AddPacket(
            mediapipe::MakePacket<absl::optional<T>>(output).At(
                cc->Inputs().Tag(TickTag).Value().Timestamp()));

        return absl::OkStatus();
    }
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_CALCULATORS_OPTIONAL_CALCULATOR_H