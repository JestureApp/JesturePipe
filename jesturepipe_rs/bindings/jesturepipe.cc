
#include "jesturepipe_rs/bindings/jesturepipe.h"

#include "absl/status/status.h"
#include "jesturepipe/graphs/jesturepipe/jesturepipe.h"
#include "mediapipe/framework/calculator_framework.h"

constexpr char PalmModelPathTag[] = "palm_model_path";
constexpr char HandModelPathTag[] = "landmark_model_path";
constexpr char CameraIndexTag[] = "camera_index";
constexpr char NumHandsTag[] = "num_hands";

extern "C" {
Status* status_new(absl::Status absl_status) {
    Status* status = new Status;

    status->code = absl_status.raw_code();

    if (status->code == 0) {
        status->message = nullptr;
        return status;
    }

    char* message = new char[absl_status.message().length()];
    memcpy(message, absl_status.message().data(),
           absl_status.message().length());

    status->message = message;

    return status;
}

void status_free(Status* status) {
    if (status->message != nullptr) {
        delete status->message;
    }

    delete status;
}

Status* fails() { return status_new(absl::InternalError("This is a test")); }

typedef struct JesturePipe {
    mediapipe::CalculatorGraph graph;
    std::map<std::string, mediapipe::Packet> init_side_packets;
} JesturePipe;

JesturePipe* jesturepipe_new(const char* palm_model_path,
                             const int palm_model_len,
                             const char* hand_model_path,
                             const int hand_model_len) {
    JesturePipe* pipe = new JesturePipe{
        .init_side_packets = {
            {PalmModelPathTag, mediapipe::MakePacket<std::string>(std::string(
                                   palm_model_path, palm_model_len))},
            {HandModelPathTag, mediapipe::MakePacket<std::string>(std::string(
                                   hand_model_path, hand_model_len))}}};

    return pipe;
}

void jesturepipe_free(JesturePipe* pipe) { delete pipe; }

Status* jesturepipe_initialize(JesturePipe* pipe) {
    absl::Status status =
        jesturepipe::jesturepipe_graph(&pipe->graph, pipe->init_side_packets);

    return status_new(status);
}

Status* jesturepipe_start(JesturePipe* pipe, int camera_index, int num_hands) {
    absl::Status status = pipe->graph.StartRun({
        {CameraIndexTag, mediapipe::MakePacket<int>(camera_index)},
        {NumHandsTag, mediapipe::MakePacket<int>(num_hands)},
    });

    return status_new(status);
}

Status* jesturepipe_stop(JesturePipe* pipe) {
    absl::Status status = pipe->graph.CloseAllPacketSources();

    if (!status.ok()) {
        return status_new(status);
    }

    status.Update(pipe->graph.WaitUntilDone());

    return status_new(status);
}
}