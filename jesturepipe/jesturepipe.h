#ifndef JESTUREPIPE_JESTUREPIPE_H
#define JESTUREPIPE_JESTUREPIPE_H

#include <string>

#include "absl/status/status.h"
#include "mediapipe/framework/calculator_graph.h"

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
    absl::Status Start();

    /// \brief Stops the pipeline. This method will block until the pipeline has
    /// exited.
    /// \return A status indicating the success of stopping the graph.
    /// An ok status if the graph stopped successfully or an error status
    /// otherwise.
    absl::Status Stop();
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_JESTUREPIPE_H