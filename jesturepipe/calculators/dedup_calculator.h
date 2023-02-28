#ifndef JESTUREPIPE_CALCULATORS_DEDUP_CALCULATOR_H
#define JESTUREPIPE_CALCULATORS_DEDUP_CALCULATOR_H

#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/logging.h"

namespace jesturepipe {

template <typename T>
class DedupCalculator : public mediapipe::CalculatorBase {
   public:
    ~DedupCalculator() { delete last; }

    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Inputs().Index(0).Set<T>();
        cc->Outputs().Index(0).Set<T>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        auto& input = cc->Inputs().Index(0);
        auto& output = cc->Outputs().Index(0);

        if (!input.Header().IsEmpty()) output.SetHeader(input.Header());

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        auto& input = cc->Inputs().Index(0);
        auto& output = cc->Outputs().Index(0);

        T val = input.Get<T>();

        if (last == nullptr || val != *last) {
            output.AddPacket(
                mediapipe::MakePacket<T>(val).At(input.Value().Timestamp()));

            delete last;
            last = new T(val);
        } else {
            // std::cout << cc->NodeName()
            //           << ": found duplicate, setting timestamp bound to "
            //           << cc->InputTimestamp().NextAllowedInStream()
            //           << std::endl;

            output.SetNextTimestampBound(
                cc->InputTimestamp().NextAllowedInStream());
        }

        return absl::OkStatus();
    }

   private:
    T* last = nullptr;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_CALCULATORS_DEDUP_CALCULATOR_H