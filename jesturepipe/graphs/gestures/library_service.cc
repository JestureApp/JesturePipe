#include "jesturepipe/graphs/gestures/library_service.h"

namespace jesturepipe {

const mediapipe::GraphService<GestureLibrary> GestureLibraryService(
    "gesture_library_service",
    mediapipe::GraphServiceBase::GraphServiceBase::kAllowDefaultInitialization);

}  // namespace jesturepipe