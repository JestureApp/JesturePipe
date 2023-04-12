#include "jesturepipe/jesturepipe.h"

#include "absl/status/statusor.h"
#include "glog/logging.h"
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

        input_stream: "frame"
        input_stream: "is_recording"

        output_stream: "gesture_id"
        output_stream: "recorded_gesture"
        output_stream: "multi_hand_landmarks"
        output_stream: "hand_presence"

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
          input_stream: "NORM_LANDMARKS:multi_hand_landmarks"
        }
    )pb");
}

JesturePipe::JesturePipe()
    : mediapipe::CalculatorGraph(),
      running(false),
      recording(false),
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

    LOG(INFO) << "Initializing JesturePipe";

    absl::Status status =
        CalculatorGraph::Initialize(graph_config(), side_packets);

    return status;
}

bool JesturePipe::isRunning() const { return running; }

absl::Status JesturePipe::Start(bool use_full) {
    using namespace mediapipe;

    if (running) return absl::OkStatus();

    std::map<std::string, Packet> side_packets;

    side_packets["use_full"] = MakePacket<bool>(use_full);

    LOG(INFO) << "Starting JesturePipe with (use_full=" << use_full << ")";

    absl::Status status = CalculatorGraph::StartRun(side_packets);

    running = true;

    return status;
}

absl::Status JesturePipe::Stop() {
    using namespace mediapipe;

    if (!running) return absl::OkStatus();

    LOG(INFO) << "Stopping JesturePipe";

    absl::Status status = CalculatorGraph::CloseAllInputStreams();

    if (!status.ok()) return status;

    status.Update(CalculatorGraph::CloseAllPacketSources());

    if (!status.ok()) return status;

    status.Update(CalculatorGraph::WaitUntilDone());

    running = false;

    return status;
}

absl::Status JesturePipe::AddFrame(std::unique_ptr<mediapipe::ImageFrame> frame,
                                   unsigned long timestamp) {
    using namespace mediapipe;

    return CalculatorGraph::AddPacketToInputStream(
        "frame",
        mediapipe::Adopt(frame.release()).At(mediapipe::Timestamp(timestamp)));
}

absl::Status JesturePipe::OnGestureRecognition(
    std::function<absl::Status(int gesture_id, unsigned long timestamp)>
        packet_callback) {
    using namespace mediapipe;

    return CalculatorGraph::ObserveOutputStream(
        "gesture_id", [packet_callback](const mediapipe::Packet& packet) {
            return packet_callback(packet.Get<int>(),
                                   packet.Timestamp().Value());
        });
}

absl::Status JesturePipe::OnRecordedGesture(
    std::function<absl::Status(Gesture gesture, unsigned long timestamp)>
        packet_callback) {
    using namespace mediapipe;

    return CalculatorGraph::ObserveOutputStream(
        "recorded_gesture", [packet_callback](const mediapipe::Packet& packet) {
            return packet_callback(packet.Get<Gesture>(),
                                   packet.Timestamp().Value());
        });
}

absl::Status JesturePipe::OnLandmarks(
    std::function<absl::Status(
        std::vector<mediapipe::NormalizedLandmarkList> multi_hand_landmarks,
        unsigned long timestamp)>
        packet_callback) {
    using namespace mediapipe;

    return CalculatorGraph::ObserveOutputStream(
        "multi_hand_landmarks",
        [packet_callback](const mediapipe::Packet& packet) {
            return packet_callback(
                packet.Get<std::vector<mediapipe::NormalizedLandmarkList>>(),
                packet.Timestamp().Value());
        });
}

absl::Status JesturePipe::OnHandPresence(
    std::function<absl::Status(bool present, unsigned long timestamp)>
        packet_callback) {
    using namespace mediapipe;

    return CalculatorGraph::ObserveOutputStream(
        "hand_presence", [packet_callback](const mediapipe::Packet& packet) {
            return packet_callback(packet.Get<bool>(),
                                   packet.Timestamp().Value());
        });
}

bool JesturePipe::IsRecording() const { return recording; }

absl::Status JesturePipe::SetRecording(bool recording) {
    using namespace mediapipe;

    this->recording = recording;

    return CalculatorGraph::AddPacketToInputStream(
        "is_recording",
        MakePacket<bool>(recording).At(Timestamp(recording_ts++)));
}

void JesturePipe::SetGesture(int id, Gesture gesture) {
    LOG(INFO) << "Added gesture with id " << id << " and frames " << gesture;
    library->Set(id, std::move(gesture));
}

void JesturePipe::RemoveGesture(int gesture_id) { library->Remove(gesture_id); }

void JesturePipe::ClearGestures() {
    library->Clear();

    std::unique_lock<std::shared_mutex> lk(actions->mutex);
    actions->mapping.clear();
}

void JesturePipe::SetAction(int gesture_id, ActionList action) {
    std::unique_lock<std::shared_mutex> lk(actions->mutex);

    actions->mapping[gesture_id] = action;
}

void JesturePipe::RemoveAction(int gesture_id) {
    std::unique_lock<std::shared_mutex> lk(actions->mutex);

    actions->mapping.erase(gesture_id);
}

}  // namespace jesturepipe