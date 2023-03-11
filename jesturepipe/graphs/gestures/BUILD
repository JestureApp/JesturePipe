load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

mediapipe_simple_subgraph(
    name = "gestures",
    graph = "gestures.pbtxt",
    register_as = "Gestures",
    deps = [
        "//jesturepipe/calculators:echoer_calculator",
        "//jesturepipe/calculators:get_vector_item_calculator",
        "//jesturepipe/graphs/gestures/calculators:gesture_frame_constructor_calculator",
        "//jesturepipe/graphs/gestures/calculators:gesture_recognizer_calculator",
        "//jesturepipe/graphs/hands",
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
        "@mediapipe//mediapipe/calculators/util:clock_timestamp_calculator",
    ],
)

cc_library(
    name = "library_service",
    srcs = ["library_service.cc"],
    hdrs = ["library_service.h"],
    deps = [
        "//jesturepipe/gesture:library",
        "@mediapipe//mediapipe/framework:calculator_framework",
    ],
)
