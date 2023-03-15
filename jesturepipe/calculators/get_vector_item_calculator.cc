
#include "mediapipe/calculators/core/get_vector_item_calculator.h"

#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {
using GetNormalizedLandmarkListVectorItemCalculator =
    mediapipe::api2::GetVectorItemCalculator<mediapipe::NormalizedLandmarkList>;
REGISTER_CALCULATOR(GetNormalizedLandmarkListVectorItemCalculator);
}  // namespace jesturepipe