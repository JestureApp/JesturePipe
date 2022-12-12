#ifndef __H_JESTUREPIPE_CALCULATORS_DEDUP_CALCULATOR__
#define __H_JESTUREPIPE_CALCULATORS_DEDUP_CALCULATOR__

#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"
#include "type_traits"

namespace jesturepipe {
template <typename T>
class DedupCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Inputs().Index(0).Set<T>();
        cc->Outputs().Index(0).Set<T>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        auto input = cc->Inputs().Index(0).Get<T>();

        return absl::OkStatus();
    }

   private:
    T& last_packet_;
};
}  // namespace jesturepipe

#endif  // __H_JESTUREPIPE_CALCULATORS_DEDUP_CALCULATOR__