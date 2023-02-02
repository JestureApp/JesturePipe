#include <unistd.h>

#include <tuple>
#include <vector>

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

class GestureRecorder : public mediapipe::CalculatorBase {
   public:
    static absl::Status GetContract(mediapipe::CalculatorContract* cc) {
        cc->Inputs().Tag(LandmarksTag).Set<mediapipe::NormalizedLandmarkList>();

        // cc->Outputs().Tag(GestureFeatureTag).Set<GestureFeature>();

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
        // Skip the process if custom gesture has been created or is unwanted
        GestureStore& instance = GestureStore::get_instance();
        if (instance.finished_custom_gesture) return absl::OkStatus();

        // start-->prompt
        // recordin
        if (!instance.to_record) {
            std::string input;
            std::cout << "Press s to start recording custom gesture and to "
                         "skip recording press q: ";
            std::cin >> input;
            if (input == "s") {
                instance.to_record = true;
                instance.start_time = time(0);
            } else if (input == "q") {
                instance.to_record = false;
                instance.finished_custom_gesture = true;
            }
        }
        double seconds_since_start = difftime(time(0), instance.start_time);
        if (instance.to_record && !instance.finished_custom_gesture &&
            seconds_since_start > 7) {
            instance.to_record = false;
            instance.finished_custom_gesture = true;
            std::cout << "Storing new gesture..." << std::endl;
            CustomGestureFeatureAggregate();
            // Maybe print out the coordinates to show?
            std::cout << "Custom Gesture has been recorded!" << std::endl;
        }

        feature.index_vertical = GetFingerDirectionVertical(
            landmarks.landmark()[INDEX_FINGER_TIP].y() -
            landmarks.landmark()[INDEX_FINGER_PIP].y());

        feature.index_horizontal = GetFingerDirectionHorizontal(
            landmarks.landmark()[INDEX_FINGER_TIP].x() -
            landmarks.landmark()[INDEX_FINGER_PIP].x());

        feature.middle_vertical = GetFingerDirectionVertical(
            landmarks.landmark()[MIDDLE_FINGER_TIP].y() -
            landmarks.landmark()[MIDDLE_FINGER_PIP].y());

        feature.middle_horizontal = GetFingerDirectionHorizontal(
            landmarks.landmark()[MIDDLE_FINGER_TIP].x() -
            landmarks.landmark()[MIDDLE_FINGER_PIP].x());

        feature.ring_vertical = GetFingerDirectionVertical(
            landmarks.landmark()[RING_FINGER_TIP].y() -
            landmarks.landmark()[RING_FINGER_PIP].y());

        feature.ring_horizontal = GetFingerDirectionHorizontal(
            landmarks.landmark()[RING_FINGER_TIP].x() -
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
                         landmarks.landmark()[MIDDLE_FINGER_PIP].x(),
                     landmarks.landmark()[MIDDLE_FINGER_TIP].y() -
                         landmarks.landmark()[MIDDLE_FINGER_PIP].y());

        feature.middle_angle =
            GetAngle(landmarks.landmark()[MIDDLE_FINGER_TIP].x() -
                         landmarks.landmark()[MIDDLE_FINGER_PIP].x(),
                     landmarks.landmark()[MIDDLE_FINGER_TIP].y() -
                         landmarks.landmark()[MIDDLE_FINGER_PIP].y());

        feature.thumb_index_vertical = GetFingerDirectionVertical(
            landmarks.landmark()[THUMB_TIP].y() -
            landmarks.landmark()[INDEX_FINGER_TIP].y());

        // Adds the feature of the current frame to a persistent list to record
        // custom gestures
        if (instance.to_record && !instance.finished_custom_gesture)
            AddFeatureForCustomGesture(feature);
        // Ask
        // cc->Outputs()
        //     .Tag(GestureFeatureTag)
        //     .AddPacket(mediapipe::MakePacket<GestureFeature>(feature).At(
        //         cc->InputTimestamp()));

        return absl::OkStatus();
    }

   private:
    static void AddFeatureForCustomGesture(GestureFeature feature) {
        GestureStore& instance = GestureStore::get_instance();
        instance.features.push_back(feature);
    }

    static FingerDirection GetFingerDirectionVertical(double dy) {
        if (dy < 0)
            return FingerDirection::Up;
        else if (dy > 0)
            return FingerDirection::Down;
    }
    static FingerDirection GetFingerDirectionHorizontal(double dx) {
        if (dx < 0)
            return FingerDirection::Left;
        else if (dx > 0)
            return FingerDirection::Right;
    }
    static double GetAngle(double dx, double dy) {
        double theta = atan2(-dy, dx);
        return theta * (180 / M_PI);
    }

   private:
    static void CustomGestureFeatureAggregate() {
        GestureStore& instance = GestureStore::get_instance();
        std::vector<GestureFeature> features = instance.features;
        std::tuple<int, int, int, int> index(0, 0, 0, 0);
        std::tuple<int, int, int, int> middle(0, 0, 0, 0);
        std::tuple<int, int, int, int> ring(0, 0, 0, 0);
        std::tuple<int, int, int, int> pinky(0, 0, 0, 0);
        std::tuple<int, int, int, int> thumb(0, 0, 0, 0);

        for (GestureFeature feature : features) {
            // index
            if (feature.index_vertical == FingerDirection::Up)
                std::get<0>(index) += 1;
            else
                std::get<1>(index) += 1;

            if (feature.index_horizontal == FingerDirection::Left)
                std::get<2>(index) += 1;
            else
                std::get<3>(index) += 1;

            // middle
            if (feature.middle_vertical == FingerDirection::Up)
                std::get<0>(middle) += 1;
            else
                std::get<1>(middle) += 1;

            if (feature.middle_horizontal == FingerDirection::Left)
                std::get<2>(middle) += 1;
            else
                std::get<3>(middle) += 1;

            // ring
            if (feature.ring_vertical == FingerDirection::Up)
                std::get<0>(ring) += 1;
            else
                std::get<1>(ring) += 1;

            if (feature.ring_horizontal == FingerDirection::Left)
                std::get<2>(ring) += 1;
            else
                std::get<3>(ring) += 1;

            // pinky
            if (feature.pinky_vertical == FingerDirection::Up)
                std::get<0>(pinky) += 1;
            else
                std::get<1>(pinky) += 1;

            if (feature.pinky_horizontal == FingerDirection::Left)
                std::get<2>(pinky) += 1;
            else
                std::get<3>(pinky) += 1;

            // thumb
            if (feature.thumb_vertical == FingerDirection::Up)
                std::get<0>(thumb) += 1;
            else
                std::get<1>(thumb) += 1;

            if (feature.thumb_horizontal == FingerDirection::Left)
                std::get<2>(thumb) += 1;
            else
                std::get<3>(thumb) += 1;
        }
        GestureFeature final_custom_feature;
        // Compare (1, 2) - Vertical and (3, 4) - Horizontal
        if (std::get<0>(index) > std::get<1>(index)) {
            final_custom_feature.index_vertical = FingerDirection::Up;
        } else {
            final_custom_feature.index_vertical = FingerDirection::Down;
        }

        if (std::get<2>(index) > std::get<3>(index)) {
            final_custom_feature.index_horizontal = FingerDirection::Left;
        } else {
            final_custom_feature.index_horizontal = FingerDirection::Right;
        }

        // Middle
        if (std::get<0>(middle) > std::get<1>(middle)) {
            final_custom_feature.middle_vertical = FingerDirection::Up;
        } else {
            final_custom_feature.middle_vertical = FingerDirection::Down;
        }

        if (std::get<2>(middle) > std::get<3>(middle)) {
            final_custom_feature.middle_horizontal = FingerDirection::Left;
        } else {
            final_custom_feature.middle_horizontal = FingerDirection::Right;
        }

        // Ring
        if (std::get<0>(ring) > std::get<1>(ring))
            final_custom_feature.ring_vertical = FingerDirection::Up;
        else
            final_custom_feature.ring_vertical = FingerDirection::Down;

        if (std::get<2>(ring) > std::get<3>(ring)) {
            final_custom_feature.ring_horizontal = FingerDirection::Left;
        } else {
            final_custom_feature.ring_horizontal = FingerDirection::Right;
        }

        // Pinky
        if (std::get<0>(pinky) > std::get<1>(pinky))
            final_custom_feature.pinky_vertical = FingerDirection::Up;
        else
            final_custom_feature.pinky_vertical = FingerDirection::Down;

        if (std::get<2>(pinky) > std::get<3>(pinky)) {
            final_custom_feature.pinky_horizontal = FingerDirection::Left;
        } else {
            final_custom_feature.pinky_horizontal = FingerDirection::Right;
        }

        // Thumb
        if (std::get<0>(thumb) > std::get<1>(thumb))
            final_custom_feature.thumb_vertical = FingerDirection::Up;
        else
            final_custom_feature.thumb_vertical = FingerDirection::Down;

        if (std::get<2>(thumb) > std::get<3>(thumb))
            final_custom_feature.thumb_horizontal = FingerDirection::Left;
        else
            final_custom_feature.thumb_horizontal = FingerDirection::Right;

        instance.final_feature = final_custom_feature;
    }
};

REGISTER_CALCULATOR(GestureRecorder);
}  // namespace jesturepipe