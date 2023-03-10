#include "absl/strings/str_format.h"
#include "mediapipe/calculators/util/packet_frequency.pb.h"
#include "mediapipe/framework/api2/node.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/util/color.pb.h"
#include "mediapipe/util/render_data.pb.h"

namespace jesturepipe {

namespace api2 = mediapipe::api2;

class FpsToRenderDataCalculator : public api2::Node {
   public:
    static constexpr api2::Input<mediapipe::PacketFrequency> kFps{"FPS"};
    static constexpr api2::Output<mediapipe::RenderData> kRenderData{
        "RENDER_DATA"};

    MEDIAPIPE_NODE_CONTRACT(kFps, kRenderData)

    static absl::Status UpdateContract(mediapipe::CalculatorContract *cc) {
        cc->SetProcessTimestampBounds(true);
        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext *cc) override {
        using namespace mediapipe;

        double fps = kFps(cc).IsEmpty() ? 0.0 : kFps(cc)->packet_frequency_hz();

        RenderData render_data;

        auto *fps_annotation = render_data.add_render_annotations();
        fps_annotation->mutable_color()->set_r(0);
        fps_annotation->mutable_color()->set_g(255);
        fps_annotation->mutable_color()->set_b(0);

        auto *fps_text = fps_annotation->mutable_text();
        fps_text->set_display_text(absl::StrFormat("FPS: %2.2f", fps));
        fps_text->set_font_height(10);
        fps_text->set_left(10);
        fps_text->set_baseline(20);

        kRenderData(cc).Send(std::move(render_data), cc->InputTimestamp());

        return absl::OkStatus();
    }
};

MEDIAPIPE_REGISTER_NODE(FpsToRenderDataCalculator);

}  // namespace jesturepipe