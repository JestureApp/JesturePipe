#include "jesturepipe/gesture/gesture.h"
#include "jesturepipe/gesture/recognizer.h"
#include "jesturepipe/graphs/gestures/library_service.h"
#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesturepipe {

namespace api2 = mediapipe::api2;

class GestureRecognizerCalculator : public api2::Node {
   public:
    static constexpr api2::SideInput<double> kThresh{"THRESH"};
    static constexpr api2::SideInput<std::shared_ptr<GestureLibrary>> kLibrary{
        "LIBRARY"};

    static constexpr api2::Input<GestureFrame> kFrames{"GESTURE_FRAME"};

    static constexpr api2::Output<int> kGestureId{"GESTURE_ID"};

    MEDIAPIPE_NODE_CONTRACT(kThresh, kLibrary, kFrames, kGestureId)

    static absl::Status UpdateContract(mediapipe::CalculatorContract *cc) {
        cc->SetProcessTimestampBounds(true);
        // cc->UseService(GestureLibraryService);

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext *cc) override {
        cc->SetOffset(mediapipe::TimestampDiff(0));

        recognizer = GestureRecognizer(*kLibrary(cc), *kThresh(cc));

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        if (kFrames(cc).IsEmpty()) {
            recognizer.Reset();
            return absl::OkStatus();
        }

        GestureFrame frame = *kFrames(cc);

        absl::optional<int> gesture_id = recognizer.ProcessFrame(frame);

        if (gesture_id.has_value())
            kGestureId(cc).Send(gesture_id.value(), cc->InputTimestamp());

        return absl::OkStatus();
    }

   private:
    GestureRecognizer recognizer;
};

MEDIAPIPE_REGISTER_NODE(GestureRecognizerCalculator);

}  // namespace jesturepipe