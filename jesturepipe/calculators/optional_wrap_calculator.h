#ifndef JESTUREPIPE_CALCULATORS_OPTIONAL_WRAP_CALCULATOR_H
#define JESTUREPIPE_CALCULATORS_OPTIONAL_WRAP_CALCULATOR_H

#include "absl/types/optional.h"
#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {

namespace api2 = mediapipe::api2;

template <typename T>
class OptionalWrapCalculator : public api2::Node {
    static constexpr api2::Input<T> kIn{};
    static constexpr api2::Output<absl::optional<T>> kOut{};

    MEDIAPIPE_NODE_CONTRACT(kIn, kOut)

    static absl::Status UpdateContract(mediapipe::CalculatorContract *cc) {
        cc->SetProcessTimestampBounds(true);
        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        absl::optional<T> out;

        if (!kIn(cc).IsEmpty()) out = *kIn(cc);

        kOut(cc).Send(std::move(out), cc->InputTimestamp());

        return absl::OkStatus();
    }
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_CALCULATORS_OPTIONAL_WRAP_CALCULATOR_H