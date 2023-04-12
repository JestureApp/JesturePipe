#include <memory>

#include "absl/status/status.h"
#include "jesturepipe/gesture/library.h"
#include "mediapipe/framework/api2/builder.h"
#include "mediapipe/framework/calculator_graph.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "tools/cpp/runfiles/runfiles.h"

using bazel::tools::cpp::runfiles::Runfiles;

constexpr char palm_full_model_path[] =
    "mediapipe/mediapipe/modules/palm_detection/palm_detection_full.tflite";

constexpr char palm_lite_model_path[] =
    "mediapipe/mediapipe/modules/palm_detection/palm_detection_full.tflite";

constexpr char hand_landmark_full_model_path[] =
    "mediapipe/mediapipe/modules/hand_landmark/hand_landmark_full.tflite";

constexpr char hand_landmark_lite_model_path[] =
    "mediapipe/mediapipe/modules/hand_landmark/hand_landmark_lite.tflite";

constexpr char window_name[] = "JesturePipe Gestures";
constexpr char frame_stream[] = "annotated_frame";
constexpr char recording_stream[] = "recorded_gesture";

using namespace jesturepipe;

mediapipe::CalculatorGraphConfig graph_config() {
    using namespace mediapipe;
    return ParseTextProtoOrDie<CalculatorGraphConfig>(R"pb(
        input_side_packet: "palm_full_model_path"
        input_side_packet: "palm_lite_model_path"
        input_side_packet: "hand_landmark_full_model_path"
        input_side_packet: "hand_landmark_lite_model_path"
        input_side_packet: "use_full"
        input_side_packet: "camera_index"
        input_side_packet: "gesture_library"

        input_stream: "is_recording"

        output_stream: "annotated_frame"
        output_stream: "recorded_gesture"

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

std::shared_ptr<GestureLibrary> init_library() {
    std::shared_ptr<GestureLibrary> library =
        std::make_shared<GestureLibrary>();

    library->Set(0, Gesture::Stop());
    library->Set(2, Gesture::Pause());
    library->Set(3, Gesture::Prev());
    library->Set(4, Gesture::Next());
    library->Set(1, Gesture::SlideLeft());
    library->Set(5, Gesture::SlideRight());
    // library->Set(6, Gesture::CustomGesture());
    return library;
}

absl::Status on_recording(mediapipe::Packet packet) {
    Gesture gesture = packet.Get<Gesture>(); 

    std::cout << "Recorded gesture with frames:" << std::endl;

    for (GestureFrame frame : *gesture.frames) {
        std::cout << "GestureFrame{" << std::endl;
        std::cout << "\tHandShape{" << std::endl;
        std::cout << "\t\tindex_direction: " << frame.hand_shape.index_direction
                  << std::endl;
        std::cout << "\t\tmiddle_direction: "
                  << frame.hand_shape.middle_direction << std::endl;
        std::cout << "\t\tring_direction: " << frame.hand_shape.ring_direction
                  << std::endl;
        std::cout << "\t\tpinky_direction: " << frame.hand_shape.pinky_direction
                  << std::endl;
        std::cout << "\t\tthumb_direction: " << frame.hand_shape.thumb_direction
                  << std::endl;
        std::cout << "\t}" << std::endl;

        if (frame.movement_direction.has_value())
            std::cout << "movement_direction: "
                      << frame.movement_direction.value() << std::endl;

        std::cout << "}" << std::endl;
    }

    return absl::OkStatus();
}

absl::Status run(Runfiles* runfiles, int camera_index, bool use_full) {
    using namespace mediapipe;

    CalculatorGraph graph;

    std::shared_ptr<GestureLibrary> library = init_library();

    std::map<std::string, Packet> init_side_packets;

    init_side_packets["palm_full_model_path"] =
        MakePacket<std::string>(runfiles->Rlocation(palm_full_model_path));
    init_side_packets["palm_lite_model_path"] =
        MakePacket<std::string>(runfiles->Rlocation(palm_lite_model_path));
    init_side_packets["hand_landmark_full_model_path"] =
        MakePacket<std::string>(
            runfiles->Rlocation(hand_landmark_full_model_path));
    init_side_packets["hand_landmark_lite_model_path"] =
        MakePacket<std::string>(
            runfiles->Rlocation(hand_landmark_lite_model_path));
    init_side_packets["gesture_library"] =
        MakePacket<std::shared_ptr<GestureLibrary>>(library);

    MP_RETURN_IF_ERROR(graph.Initialize(graph_config(), init_side_packets));

    std::map<std::string, Packet> run_side_packets;

    run_side_packets["camera_index"] = MakePacket<int>(camera_index);
    run_side_packets["use_full"] = MakePacket<bool>(use_full);

    cv::namedWindow(window_name);

    MP_RETURN_IF_ERROR(
        graph.ObserveOutputStream(recording_stream, on_recording));

    ASSIGN_OR_RETURN(OutputStreamPoller poller,
                     graph.AddOutputStreamPoller(frame_stream));

    LOG(INFO) << "Starting Graph";

    MP_RETURN_IF_ERROR(graph.StartRun(run_side_packets));

    bool is_recording = false;
    int next_ts = 0;

    while (true) {
        Packet frame_packet;

        if (!poller.Next(&frame_packet)) break;

        auto& output_frame = frame_packet.Get<ImageFrame>();
        cv::Mat output_frame_mat = mediapipe::formats::MatView(&output_frame);

        cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);

        cv::imshow(window_name, output_frame_mat);

        const int pressed_key = cv::waitKey(5);

        if (pressed_key >= 0 && pressed_key != 255 && pressed_key != 32) break;

        if (pressed_key == 32) {
            is_recording = !is_recording;
            MP_RETURN_IF_ERROR(graph.AddPacketToInputStream(
                "is_recording", mediapipe::MakePacket<bool>(is_recording)
                                    .At(mediapipe::Timestamp(next_ts++))));
        }
    }

    LOG(INFO) << "Exiting Graph";

    MP_RETURN_IF_ERROR(graph.CloseAllInputStreams());
    MP_RETURN_IF_ERROR(graph.CloseAllPacketSources());

    return graph.WaitUntilDone();
}

int main(int argc, char** argv) {
    int camera_index = 0;
    bool use_full = false;

    google::InitGoogleLogging(argv[0]);
    FLAGS_alsologtostderr = 1;

    std::string error;
    Runfiles* runfiles = Runfiles::Create(argv[0], &error);

    if (runfiles == nullptr) {
        LOG(ERROR) << "Failed to load runfiles: " << error;
        return EXIT_FAILURE;
    }

    absl::Status status = run(runfiles, camera_index, use_full);

    delete runfiles;

    if (!status.ok()) {
        LOG(ERROR) << "Failed to run graph: " << status.message();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}