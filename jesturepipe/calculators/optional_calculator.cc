#include "jesturepipe/calculators/optional_calculator.h"

#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {
typedef OptionalCalculator<mediapipe::NormalizedLandmarkList>
    OptionalNormalizedLandmarkListCalculator;

REGISTER_CALCULATOR(OptionalNormalizedLandmarkListCalculator);

typedef OptionalCalculator<std::vector<mediapipe::NormalizedLandmarkList>>
    OptionalNormalizedLandmarkListVectorCalculator;

REGISTER_CALCULATOR(OptionalNormalizedLandmarkListVectorCalculator);

}  // namespace jesturepipe