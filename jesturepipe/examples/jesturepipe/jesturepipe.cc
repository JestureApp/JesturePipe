#include "jesturepipe/jesturepipe.h"

#include <memory>

#include "absl/status/status.h"
#include "actions/action/keystroke.h"
#include "jesturepipe/gesture/library.h"
#include "mediapipe/framework/calculator_graph.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
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

constexpr char window_name[] = "JesturePipe";

using namespace jesturepipe;

absl::Status run(Runfiles* runfiles, int camera_index, bool use_full) {
    using namespace mediapipe;
    JesturePipeConfig config{
        .palm_model_full_path = runfiles->Rlocation(palm_full_model_path),
        .palm_model_lite_path = runfiles->Rlocation(palm_lite_model_path),
        .hand_landmark_model_full_path =
            runfiles->Rlocation(hand_landmark_full_model_path),
        .hand_landmark_model_lite_path =
            runfiles->Rlocation(hand_landmark_lite_model_path)};

    JesturePipe jesturepipe;

    jesturepipe.AddGesture(0, Gesture::Stop());

    auto pgdown_action = actions::action::ParseKeystroke("Page_Down");

    if (!pgdown_action.ok()) return pgdown_action.status();

    jesturepipe.AddAction(0, pgdown_action.value());

    MP_RETURN_IF_ERROR(jesturepipe.Initialize(config));

    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    ASSIGN_OR_RETURN(OutputStreamPoller poller, jesturepipe.FramePoller());

    LOG(INFO) << "Starting Graph";
    MP_RETURN_IF_ERROR(jesturepipe.Start(0));

    while (true) {
        Packet frame_packet;

        if (!poller.Next(&frame_packet)) break;

        auto& output_frame = frame_packet.Get<ImageFrame>();
        cv::Mat output_frame_mat = mediapipe::formats::MatView(&output_frame);

        cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);

        cv::imshow(window_name, output_frame_mat);

        const int pressed_key = cv::waitKey(5);

        if (pressed_key == 32)
            MP_RETURN_IF_ERROR(
                jesturepipe.SetRecording(!jesturepipe.IsRecording()));

        if (pressed_key >= 0 && pressed_key != 255 && pressed_key != 32) break;
    }

    LOG(INFO) << "Exiting Graph";

    return jesturepipe.Stop();
}

int main(int argc, char** argv) {
    int camera_index = 0;
    bool use_full = false;

    google::InitGoogleLogging(argv[0]);

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