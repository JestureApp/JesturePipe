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
        ":gesture_recognizer_graph",
        "//jesturepipe/calculators:echoer_calculator",
        "//jesturepipe/calculators:fixed_length_vector_calculator",
        "//jesturepipe/graphs/gestures/calculators:calc_ext",
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "gesture_recognizer_graph",
    graph = "gesture_recognizer.pbtxt",
    register_as = "GestureRecognizer2",
    deps = [
        "//jesturepipe/calculators:echoer_calculator",
        "//jesturepipe/calculators:fixed_length_vector_calculator",
        "//jesturepipe/calculators:sync_with_calculator",
        "//jesturepipe/graphs/gestures/calculators:calc_ext",
        "//jesturepipe/graphs/gestures/calculators:gesture_recognizer_calculator",
        "//jesturepipe/graphs/gestures/calculators:landmark_to_gesture_frame_calculator",
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
        "@mediapipe//mediapipe/calculators/core:gate_calculator",
        "@mediapipe//mediapipe/calculators/core:packet_cloner_calculator",
        "@mediapipe//mediapipe/calculators/core:packet_sequencer_calculator",
    ],
)
