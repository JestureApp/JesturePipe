#include <iostream>

#include "absl/strings/str_format.h"
#include "absl/types/optional.h"
#include "jesturepipe/gesture/gesture.h"
#include "mediapipe/calculators/util/packet_frequency.pb.h"
#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/util/color.pb.h"
#include "mediapipe/util/render_data.pb.h"

namespace jesturepipe {

namespace api2 = mediapipe::api2;

class DebugRenderDataCalculator : public api2::Node {
   public:
    static constexpr api2::Input<mediapipe::PacketFrequency> kFps{"FPS"};
    static constexpr api2::Input<bool> kHandPresence{"HAND_PRESENCE"};

    static constexpr api2::Input<GestureFrame>::Optional kGestureFrame{
        "GESTURE_FRAME"};
    static constexpr api2::Input<bool>::Optional kIsRecording{"IS_REC"};

    static constexpr api2::Input<int>::Optional kGestureId{"GESTURE_ID"};

    static constexpr api2::Output<mediapipe::RenderData> kRenderData{
        "RENDER_DATA"};

    MEDIAPIPE_NODE_CONTRACT(kFps, kHandPresence, kGestureFrame, kGestureId,
                            kIsRecording, kRenderData)

    static absl::Status UpdateContract(mediapipe::CalculatorContract *cc) {
        cc->SetProcessTimestampBounds(true);
        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        using namespace mediapipe;

        std::vector<std::string> lines;

        if (!kFps(cc).IsEmpty()) {
            double fps =
                kFps(cc).IsEmpty() ? 0.0 : kFps(cc)->packet_frequency_hz();

            lines.push_back(absl::StrFormat("FPS: %2.2f", fps));
        }

        if (kHandPresence(cc).IsConnected() && !kHandPresence(cc).IsEmpty()) {
            std::string hand_presence = *kHandPresence(cc) ? "true" : "false";

            lines.push_back(absl::StrFormat("Hand Present: %s", hand_presence));
        }

        if (kIsRecording(cc).IsConnected() && !kIsRecording(cc).IsEmpty()) {
            std::string is_recording = *kIsRecording(cc) ? "true" : "false";

            lines.push_back(absl::StrFormat("Is Recording: %s", is_recording));
        }

        if (kGestureFrame(cc).IsConnected()) {
            if (!kGestureFrame(cc).IsEmpty()) last_frame = *kGestureFrame(cc);

            if (last_frame.has_value()) {
                GestureFrame frame = last_frame.value();

                if (frame.movement_direction.has_value())
                    lines.push_back(
                        absl::StrFormat("Last Frame Direction: %3.0f",
                                        frame.movement_direction.value()));
                else
                    lines.push_back("Last Frame Direction: stationary");
            }
        }

        if (kGestureId(cc).IsConnected()) {
            if (!kGestureId(cc).IsEmpty()) last_gesture_id = *kGestureId(cc);

            if (last_gesture_id.has_value())
                lines.push_back(absl::StrFormat("Last Gesture Id: %d",
                                                last_gesture_id.value()));
        }

        RenderData render_data;

        int baseline = 20;

        for (std::string line : lines) {
            auto *annotation = render_data.add_render_annotations();

            annotation->mutable_color()->set_r(255);
            annotation->mutable_color()->set_g(0);
            annotation->mutable_color()->set_b(0);

            auto *text = annotation->mutable_text();
            text->set_display_text(line);
            text->set_font_height(10);
            text->set_left(10);
            text->set_baseline(baseline);

            baseline += 15;
        }

        kRenderData(cc).Send(std::move(render_data), cc->InputTimestamp());

        return absl::OkStatus();
    }

   private:
    absl::optional<GestureFrame> last_frame;
    absl::optional<int> last_gesture_id;
};

MEDIAPIPE_REGISTER_NODE(DebugRenderDataCalculator);

}  // namespace jesturepipe