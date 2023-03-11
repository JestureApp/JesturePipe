#ifndef JESTUREPIPE_GRAPH_GESTURES_LIBRARY_SERVICE_H
#define JESTUREPIPE_GRAPH_GESTURES_LIBRARY_SERVICE_H

#include "jesturepipe/gesture/library.h"
#include "mediapipe/framework/graph_service.h"

namespace jesturepipe {

extern const mediapipe::GraphService<GestureLibrary> GestureLibraryService;

}

#endif  // JESTUREPIPE_GRAPH_GESTURES_LIBRARY_SERVICE_H
