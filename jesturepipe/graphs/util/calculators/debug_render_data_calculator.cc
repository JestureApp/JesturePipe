#include "absl/strings/str_format.h"
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
    static constexpr api2::Output<mediapipe::RenderData> kRenderData{
        "RENDER_DATA"};

    MEDIAPIPE_NODE_CONTRACT(kFps, kHandPresence, kRenderData)

    static absl::Status UpdateContract(mediapipe::CalculatorContract *cc) {
        cc->SetProcessTimestampBounds(true);
        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        using namespace mediapipe;

        double fps = kFps(cc).IsEmpty() ? 0.0 : kFps(cc)->packet_frequency_hz();
        std::string hand_presence = *kHandPresence(cc) ? "true" : "false";

        std::vector<std::string> lines{
            absl::StrFormat("FPS: %2.2f", fps),
            absl::StrFormat("Hand Present: %s", hand_presence),
        };

        RenderData render_data;

        int baseline = 20;

        for (std::string line : lines) {
            auto *annotation = render_data.add_render_annotations();

            annotation->mutable_color()->set_r(0);
            annotation->mutable_color()->set_g(255);
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
};

MEDIAPIPE_REGISTER_NODE(DebugRenderDataCalculator);

}  // namespace jesturepipe