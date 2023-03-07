
#include <vector>

#include "absl/types/optional.h"
#include "jesturepipe/calculators/dedup_calculator.h"
#include "jesturepipe/gesture/gesture.h"
#include "mediapipe/calculators/core/begin_loop_calculator.h"
#include "mediapipe/calculators/core/end_loop_calculator.h"
#include "mediapipe/calculators/core/get_vector_item_calculator.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {
typedef mediapipe::BeginLoopCalculator<
    std::vector<absl::optional<mediapipe::NormalizedLandmarkList>>>
    BeginLoopOptionalNormalizedLandmarkListVectorCalculator;
REGISTER_CALCULATOR(BeginLoopOptionalNormalizedLandmarkListVectorCalculator);

typedef mediapipe::api2::GetVectorItemCalculator<
    absl::optional<mediapipe::NormalizedLandmarkList>>
    GetOptionalNormalizedLandmarkListVectorItemCalculator;
REGISTER_CALCULATOR(GetOptionalNormalizedLandmarkListVectorItemCalculator);

typedef DedupCalculator<absl::optional<GestureFrame>> DedupFramesCalculator;
REGISTER_CALCULATOR(DedupFramesCalculator);
}  // namespace jesturepipe