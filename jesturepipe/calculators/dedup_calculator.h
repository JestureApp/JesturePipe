#ifndef JESTUREPIPE_CALCULATORS_DEDUP_CALCULATOR_H
#define JESTUREPIPE_CALCULATORS_DEDUP_CALCULATOR_H

#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"

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

    // absl::Status Open(mediapipe::CalculatorContext* cc) override {
    //     return absl::OkStatus();
    // }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        T val = cc->Inputs().Index(0).Get<T>();

        if (last == nullptr || val != *last) {
            cc->Outputs().Index(0).AddPacket(mediapipe::MakePacket<T>(val).At(
                cc->Inputs().Index(0).Value().Timestamp()));

            delete last;
            last = new T(val);
        }

        return absl::OkStatus();
    }

   private:
    T* last = nullptr;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_CALCULATORS_DEDUP_CALCULATOR_H