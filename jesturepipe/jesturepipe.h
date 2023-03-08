#ifndef JESTUREPIPE_JESTUREPIPE_H
#define JESTUREPIPE_JESTUREPIPE_H

#include <string>

namespace jesturepipe {

/// \brief JesturePipe initial configuration.
typedef struct JesturePipeInit {
    /// An absolute path to the full palm model.
    std::string palm_model_full_path;

    /// An absolute path to the lite palm model.
    std::string palm_model_lite_path;

    /// An absolute path to the full hand landmark model.
    std::string hand_landmark_model_full_path;

    /// An absolute path to the lite hand landmark model.
    std::string hand_landmark_model_lite_path;
} JesturePipeInit;

class JesturePipe {
   public:
    JesturePipe(JesturePipeInit init);
};

}  // namespace jesturepipe

#endif  // JESTUREPIPE_JESTUREPIPE_H