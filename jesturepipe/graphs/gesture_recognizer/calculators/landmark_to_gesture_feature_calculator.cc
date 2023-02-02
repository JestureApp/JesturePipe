#include "absl/status/status.h"
#include "jesturepipe/graphs/gesture_recognizer/calculators/gesture.h"
#include "jesturepipe/graphs/gesture_recognizer/calculators/gesture_store.h"
#include "math.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {
namespace {
constexpr int WRIST = 0;
constexpr int THUMB_CMC = 1;
constexpr int THUMB_MCP = 2;
constexpr int THUMB_IP = 3;
constexpr int THUMB_TIP = 4;
constexpr int INDEX_FINGER_MCP = 5;
constexpr int INDEX_FINGER_PIP = 6;
constexpr int INDEX_FINGER_DIP = 7;
constexpr int INDEX_FINGER_TIP = 8;
constexpr int MIDDLE_FINGER_MCP = 9;
constexpr int MIDDLE_FINGER_PIP = 10;
constexpr int MIDDLE_FINGER_DIP = 11;
constexpr int MIDDLE_FINGER_TIP = 12;
constexpr int RING_FINGER_MCP = 13;
constexpr int RING_FINGER_PIP = 14;
constexpr int RING_FINGER_DIP = 15;
constexpr int RING_FINGER_TIP = 16;
constexpr int PINKY_MCP = 17;
constexpr int PINKY_PIP = 18;
constexpr int PINKY_DIP = 19;
constexpr int PINKY_TIP = 20;

constexpr char LandmarksTag[] = "LANDMARKS";
constexpr char GestureFeatureTag[] = "GESTURE_FEATURE";
}  // namespace

class LandmarkToGestureFeatureCalculator : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Inputs().Tag(LandmarksTag).Set<mediapipe::NormalizedLandmarkList>();

        cc->Outputs().Tag(GestureFeatureTag).Set<GestureFeature>();

        return absl::OkStatus();
    }

    absl::Status Open(mediapipe::CalculatorContext* cc) override {
        return absl::OkStatus();
    }

    absl::Status Process(mediapipe::CalculatorContext* cc) override {
        auto landmarks = cc->Inputs()
                             .Tag("LANDMARKS")
                             .Get<mediapipe::NormalizedLandmarkList>();

        GestureFeature feature;

        feature.index_vertical =
            GetFingerDirectionVertical(landmarks.landmark()[INDEX_FINGER_TIP].y() -
                                landmarks.landmark()[INDEX_FINGER_PIP].y());
        
        feature.index_horizontal =
            GetFingerDirectionHorizontal(landmarks.landmark()[INDEX_FINGER_TIP].x() -
                                landmarks.landmark()[INDEX_FINGER_PIP].x());
                                
        feature.middle_vertical =
            GetFingerDirectionVertical(landmarks.landmark()[MIDDLE_FINGER_TIP].y() -
                                landmarks.landmark()[MIDDLE_FINGER_PIP].y());

        feature.middle_horizontal =
            GetFingerDirectionHorizontal(landmarks.landmark()[MIDDLE_FINGER_TIP].x() -
                                landmarks.landmark()[MIDDLE_FINGER_PIP].x());

        feature.ring_vertical =
            GetFingerDirectionVertical(landmarks.landmark()[RING_FINGER_TIP].y() -
                                landmarks.landmark()[RING_FINGER_PIP].y());

        feature.ring_horizontal =
            GetFingerDirectionHorizontal(landmarks.landmark()[RING_FINGER_TIP].x() -
                                landmarks.landmark()[RING_FINGER_PIP].x());                      

        feature.pinky_vertical =
            GetFingerDirectionVertical(landmarks.landmark()[PINKY_TIP].y() -
                                landmarks.landmark()[PINKY_PIP].y());

        feature.pinky_horizontal =
            GetFingerDirectionHorizontal(landmarks.landmark()[PINKY_TIP].x() -
                                landmarks.landmark()[PINKY_PIP].x());

        feature.thumb_vertical =
            GetFingerDirectionVertical(landmarks.landmark()[THUMB_TIP].y() -
                                landmarks.landmark()[THUMB_MCP].y());

        feature.thumb_horizontal =
            GetFingerDirectionHorizontal(landmarks.landmark()[THUMB_TIP].x() -
                                landmarks.landmark()[THUMB_MCP].x());

        feature.middle_angle = 
            GetAngle(landmarks.landmark()[MIDDLE_FINGER_TIP].x() -
                                landmarks.landmark()[MIDDLE_FINGER_PIP].x(), landmarks.landmark()[MIDDLE_FINGER_TIP].y() -
                                landmarks.landmark()[MIDDLE_FINGER_PIP].y());

        feature.middle_angle = 
            GetAngle(landmarks.landmark()[MIDDLE_FINGER_TIP].x() -
                                landmarks.landmark()[MIDDLE_FINGER_PIP].x(), landmarks.landmark()[MIDDLE_FINGER_TIP].y() -
                                landmarks.landmark()[MIDDLE_FINGER_PIP].y());
        
        feature.thumb_index_vertical = 
            GetFingerDirectionVertical(landmarks.landmark()[THUMB_TIP].y() -
                                landmarks.landmark()[INDEX_FINGER_TIP].y());

        cc->Outputs()
            .Tag(GestureFeatureTag)
            .AddPacket(mediapipe::MakePacket<GestureFeature>(feature).At(
                cc->InputTimestamp()));

        return absl::OkStatus();
    }

   private:
    static FingerDirection GetFingerDirectionVertical(double dy){
        if (dy < 0)
            return FingerDirection::Up;
        else if (dy > 0)
            return FingerDirection::Down;
    }
    static FingerDirection GetFingerDirectionHorizontal(double dx){
        if (dx < 0)
            return FingerDirection::Left;
        else if (dx > 0)
            return FingerDirection::Right;
    }
    static double GetAngle(double dx, double dy){
        double theta = atan2(-dy, dx);
        return theta * (180/M_PI);
    }
};

REGISTER_CALCULATOR(LandmarkToGestureFeatureCalculator);
}  // namespace jesturepipe