#ifndef JESTUREPIPE_JESTUREPIPE_H
#define JESTUREPIPE_JESTUREPIPE_H

#include <memory>
#include <string>

#include "absl/status/status.h"
#include "jesturepipe/actions/mapper.h"
#include "jesturepipe/gesture/gesture.h"
#include "jesturepipe/gesture/library.h"
#include "mediapipe/framework/calculator_graph.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesturepipe {

/// \brief JesturePipe initial configuration.
typedef struct JesturePipeConfig {
    /// An absolute path to the full palm model.
    std::string palm_model_full_path;

    /// An absolute path to the lite palm model.
    std::string palm_model_lite_path;

    /// An absolute path to the full hand landmark model.
    std::string hand_landmark_model_full_path;

    /// An absolute path to the lite hand landmark model.
    std::string hand_landmark_model_lite_path;
} JesturePipeConfig;

/// \brief The pipeline for Jesture. Handles recognizing gestures and initiating
/// actions.
class JesturePipe : private mediapipe::CalculatorGraph {
   public:
    /// \brief Constructs a new JesturePipe
    JesturePipe();

    JesturePipe(JesturePipe&) = delete;
    JesturePipe& operator=(JesturePipe&) = delete;

    /// \brief Initializes the pipeline with the given config
    /// \param config the config to initialize the pipeline with.
    /// \return A status indicating the success of initializing the graph.
    /// An ok status if the graph initialized successfully or an error status
    /// otherwise.
    absl::Status Initialize(const JesturePipeConfig& config);

    /// \brief Starts the pipeline. The pipeline will run asynchronously and
    /// returns once the pipeline has been started.
    /// \return A status indicating the success of starting the graph.
    /// An ok status if the graph started successfully or an error status
    /// otherwise.
    absl::Status Start(bool use_full = false);

    /// \brief Stops the pipeline. This method will block until the pipeline has
    /// exited.
    /// \return A status indicating the success of stopping the graph.
    /// An ok status if the graph stopped successfully or an error status
    /// otherwise.
    absl::Status Stop();

    bool isRunning() const;

    absl::Status AddFrame(std::unique_ptr<mediapipe::ImageFrame> frame,
                          unsigned long timestamp);

    absl::Status OnGestureRecognition(
        std::function<absl::Status(int gesture_id, unsigned long timestamp)>
            packet_callback);

    absl::Status OnRecordedGesture(
        std::function<absl::Status(Gesture gesture, unsigned long timestamp)>
            packet_callback);

    absl::Status OnLandmarks(
        std::function<absl::Status(
            std::vector<mediapipe::NormalizedLandmarkList> multi_hand_landmarks,
            unsigned long timestamp)>
            packet_callback);

    absl::Status OnHandPresence(
        std::function<absl::Status(bool present, unsigned long timestamp)>
            packet_callback);

    bool IsRecording() const;

    absl::Status SetRecording(bool);

    void SetGesture(int gesture_id, Gesture gesture);

    void RemoveGesture(int gesture_id);

    void ClearGestures();

    void SetAction(int gesture_id, actions::Action action);

   private:
    // template <typename T>
    // absl::Status ConsumeOrCopyCallback()

    bool running;
    bool recording;
    int recording_ts;
    std::shared_ptr<GestureLibrary> library;
    std::shared_ptr<ActionMapper> actions;
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_JESTUREPIPE_H