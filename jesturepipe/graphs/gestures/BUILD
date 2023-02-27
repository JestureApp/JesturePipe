load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

exports_files(glob(["*.pbtxt"]))

mediapipe_simple_subgraph(
    name = "gestures_graph",
    graph = "gestures.pbtxt",
    register_as = "Gestures",
    deps = [
        "//jesturepipe/calculators:echoer_calculator",
        "//jesturepipe/calculators:fixed_length_vector_calculator",
        "//jesturepipe/graphs/gestures/calculators:calc_ext",
        "//jesturepipe/graphs/gestures/calculators:gesture_recognizer_calculator",
        "//jesturepipe/graphs/gestures/calculators:landmark_to_gesture_frame_calculator",
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
    ],
)
