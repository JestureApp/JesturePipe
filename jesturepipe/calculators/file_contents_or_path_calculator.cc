
#include "absl/status/status.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/util/resource_util.h"

namespace jesturepipe {

namespace {
constexpr char FilePathTag[] = "FILE_PATH";
constexpr char FileContentsTag[] = "FILE_CONTENTS";
constexpr char ContentsTag[] = "CONTENTS";
}  // namespace

class FileContentsOrPathCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        RET_CHECK(cc->InputSidePackets().HasTag(FilePathTag) !=
                  cc->InputSidePackets().HasTag(FileContentsTag))
            << "Either FILE_PATH or FILE_CONTENTS must be provided.";

        if (cc->InputSidePackets().HasTag(FilePathTag))
            cc->InputSidePackets().Tag(FilePathTag).Set<std::string>();

        if (cc->InputSidePackets().HasTag(FileContentsTag))
            cc->InputSidePackets().Tag(FileContentsTag).Set<std::string>();

        cc->OutputSidePackets().Tag(ContentsTag).Set<std::string>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        std::string contents;

        if (cc->InputSidePackets().HasTag(FileContentsTag)) {
            contents = std::move(
                cc->InputSidePackets().Tag(FileContentsTag).Get<std::string>());
        } else {
            std::string path =
                cc->InputSidePackets().Tag(FilePathTag).Get<std::string>();

            MP_RETURN_IF_ERROR(
                mediapipe::GetResourceContents(path, &contents, true));
        }

        cc->OutputSidePackets()
            .Tag(ContentsTag)
            .Set(mediapipe::MakePacket<std::string>(std::move(contents)));

        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        return absl::OkStatus();
    }
};

REGISTER_CALCULATOR(FileContentsOrPathCalculator);
}  // namespace jesturepipe