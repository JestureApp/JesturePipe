#include "jesturepipe/jesturepipe.h"

#include "mediapipe/framework/api2/builder.h"
#include "mediapipe/framework/port/parse_text_proto.h"

namespace jesturepipe {

mediapipe::CalculatorGraphConfig graph_config() {
    using namespace mediapipe;
    return ParseTextProtoOrDie<CalculatorGraphConfig>(R"pb(
        input_side_packet: "palm_full_model_path"
        input_side_packet: "palm_lite_model_path"
        input_side_packet: "hand_landmark_full_model_path"
        input_side_packet: "hand_landmark_lite_model_path"
        input_side_packet: "gesture_library"
        input_side_packet: "action_mapper"

        input_side_packet: "use_full"
        input_side_packet: "camera_index"

        input_stream: "is_recording"

        output_stream: "gesture_id"
        output_stream: "recorded_gesture"
        output_stream: "multi_hand_landmarks"
        output_stream: "annotated_frame"

        node {
          calculator: "CameraCalculator"
          input_side_packet: "CAMERA_INDEX:camera_index"
          output_stream: "FRAME:frame"
        }

        node {
          calculator: "IsRecordingLatch"
          input_stream: "IS_REC:is_recording"
          input_stream: "FRAME:frame"
          output_stream: "FRAME_IS_REC:frame_is_rec"
        }

        node {
          calculator: "Gestures"
          input_side_packet: "PALM_FULL_MODEL_PATH:palm_full_model_path"
          input_side_packet: "PALM_LITE_MODEL_PATH:palm_lite_model_path"
          input_side_packet: "HAND_LANDMARK_FULL_MODEL_PATH:hand_landmark_full_model_path"
          input_side_packet: "HAND_LANDMARK_LITE_MODEL_PATH:hand_landmark_lite_model_path"
          input_side_packet: "USE_FULL:use_full"
          input_side_packet: "LIBRARY:gesture_library"
          input_stream: "IMAGE:frame"
          input_stream: "FRAME_IS_REC:frame_is_rec"
          output_stream: "NORM_LANDMARKS:multi_hand_landmarks"
          output_stream: "HAND_PRESENCE:hand_presence"
          output_stream: "GESTURE_FRAME:gesture_frame"
          output_stream: "GESTURE_ID:gesture_id"
          output_stream: "RECORDED_GESTURE:recorded_gesture"
          output_stream: "ACTIONABLE_GESTURE_ID:actionable_gesture_id"
        }

        node {
          calculator: "Actions"
          input_side_packet: "ACTION_MAPPER:action_mapper"
          input_stream: "GESTURE_ID:actionable_gesture_id"
        }

        node {
          calculator: "FrameAnnotator"
          input_stream: "FRAME:frame"
          input_stream: "NORM_LANDMARKS:multi_hand_landmarks"
          input_stream: "HAND_PRESENCE:hand_presence"
          input_stream: "GESTURE_FRAME:gesture_frame"
          input_stream: "GESTURE_ID:gesture_id"
          input_stream: "IS_REC:frame_is_rec"
          output_stream: "FRAME:annotated_frame"
        }
    )pb");
}

JesturePipe::JesturePipe()
    : mediapipe::CalculatorGraph(),
      library(std::make_shared<GestureLibrary>()),
      actions(std::make_shared<ActionMapper>()) {}

absl::Status JesturePipe::Initialize(const JesturePipeConfig& config) {
    using namespace mediapipe;

    std::map<std::string, Packet> side_packets;

    side_packets["palm_full_model_path"] =
        MakePacket<std::string>(config.palm_model_full_path);

    side_packets["palm_lite_model_path"] =
        MakePacket<std::string>(config.palm_model_lite_path);

    side_packets["hand_landmark_full_model_path"] =
        MakePacket<std::string>(config.hand_landmark_model_full_path);

    side_packets["hand_landmark_lite_model_path"] =
        MakePacket<std::string>(config.hand_landmark_model_lite_path);

    side_packets["gesture_library"] =
        MakePacket<std::shared_ptr<GestureLibrary>>(library);

    side_packets["action_mapper"] =
        MakePacket<std::shared_ptr<ActionMapper>>(actions);

    absl::Status status =
        CalculatorGraph::Initialize(graph_config(), side_packets);

    return status;
}

absl::Status JesturePipe::Start(int camera_index, bool use_full) {
    using namespace mediapipe;

    std::map<std::string, Packet> side_packets;

    side_packets["camera_index"] = MakePacket<int>(camera_index);
    side_packets["use_full"] = MakePacket<bool>(use_full);

    absl::Status status = CalculatorGraph::StartRun(side_packets);

    return status;
}

absl::Status JesturePipe::Stop() {
    using namespace mediapipe;

    absl::Status status = CalculatorGraph::CloseAllInputStreams();

    if (!status.ok()) return status;

    status.Update(CalculatorGraph::CloseAllPacketSources());

    if (!status.ok()) return status;

    status.Update(CalculatorGraph::WaitUntilDone());

    return status;
}

absl::Status JesturePipe::OnGestureRecognition(
    std::function<absl::Status(const int&)> packet_callback) {
    using namespace mediapipe;

    return CalculatorGraph::ObserveOutputStream(
        "gesture_id", [packet_callback](const mediapipe::Packet& packet) {
            return packet_callback(packet.Get<int>());
        });
}

absl::Status JesturePipe::OnRecordedGesture(
    std::function<absl::Status(const Gesture&)> packet_callback) {
    using namespace mediapipe;

    return CalculatorGraph::ObserveOutputStream(
        "recorded_gesture", [packet_callback](const mediapipe::Packet& packet) {
            return packet_callback(packet.Get<Gesture>());
        });
}

absl::Status JesturePipe::OnLandmarks(
    std::function<
        absl::Status(const std::vector<mediapipe::NormalizedLandmarkList>&)>
        packet_callback) {
    using namespace mediapipe;

    return CalculatorGraph::ObserveOutputStream(
        "multi_hand_landmarks",
        [packet_callback](const mediapipe::Packet& packet) {
            return packet_callback(
                packet.Get<std::vector<mediapipe::NormalizedLandmarkList>>());
        });
}

// absl::Status JesturePipe::OnFrame(
//     std::function<absl::Status(const mediapipe::ImageFrame&)>
//     packet_callback) { using namespace mediapipe;

//     return CalculatorGraph::ObserveOutputStream(
//         "annotated_frame", [packet_callback](const mediapipe::Packet& packet)
//         {
//             return packet_callback(packet.Get<mediapipe::ImageFrame>());
//         });
// }

mediapipe::StatusOrPoller JesturePipe::FramePoller() {
    return mediapipe::CalculatorGraph::AddOutputStreamPoller("annotated_frame");
}

bool JesturePipe::IsRecording() { return recording; }

absl::Status JesturePipe::SetRecording(bool recording) {
    using namespace mediapipe;

    this->recording = recording;

    return CalculatorGraph::AddPacketToInputStream(
        "is_recording",
        MakePacket<bool>(recording).At(Timestamp(recording_ts++)));
}

void JesturePipe::AddGesture(int id, Gesture&& gesture) {
    library->Set(id, std::move(gesture));
}

void JesturePipe::AddAction(int gesture_id, actions::Action action) {
    std::unique_lock<std::shared_mutex> lk(actions->mutex);

    if (!actions->mapping.contains(gesture_id))
        actions->mapping[gesture_id] = {};

    actions->mapping[gesture_id].push_back(action);
}

}  // namespace jesturepipe