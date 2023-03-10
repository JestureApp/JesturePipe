#include "jesturepipe/jesturepipe.h"

#include "mediapipe/framework/api2/builder.h"

namespace jesturepipe {

mediapipe::CalculatorGraphConfig graph_config() {
    using namespace mediapipe::api2::builder;
    Graph graph;

    graph.SetType("JesturePipe");

    return graph.GetConfig();
}

JesturePipe::JesturePipe() : mediapipe::CalculatorGraph() {}

absl::Status JesturePipe::Initialize(const JesturePipeConfig& config) {
    using namespace mediapipe;

    std::map<std::string, Packet> side_packets;

    side_packets["palm_model_full_path"] =
        MakePacket<std::string>(config.palm_model_full_path);

    side_packets["palm_model_lite_path"] =
        MakePacket<std::string>(config.palm_model_lite_path);

    side_packets["hand_landmark_full_path"] =
        MakePacket<std::string>(config.hand_landmark_model_full_path);

    side_packets["hand_landmark_lite_path"] =
        MakePacket<std::string>(config.hand_landmark_model_lite_path);

    absl::Status status =
        CalculatorGraph::Initialize(graph_config(), side_packets);

    return status;
}

absl::Status JesturePipe::Start() {
    using namespace mediapipe;

    std::map<std::string, Packet> side_packets;

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

}  // namespace jesturepipe