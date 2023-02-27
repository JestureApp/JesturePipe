#include "jesturepipe/calculators/fixed_length_vector_calculator.h"

#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {

typedef FixedLengthVectorCalculator<mediapipe::NormalizedLandmarkList>
    FixedLengthNormalizedLandmarkListVectorCalculator;
REGISTER_CALCULATOR(FixedLengthNormalizedLandmarkListVectorCalculator);

}  // namespace jesturepipe