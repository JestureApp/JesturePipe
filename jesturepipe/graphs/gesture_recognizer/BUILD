load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

exports_files(glob(["*.pbtxt"]))

mediapipe_simple_subgraph(
    name = "gesture_recognizer_graph",
    graph = "gesture_recognizer.pbtxt",
    register_as = "GestureRecognizer",
    deps = [
        "//jesturepipe/graphs/actions:actions_graph",
        "//jesturepipe/graphs/gesture_recognizer/calculators:gesture_classifier_calculator",
        "//jesturepipe/graphs/gesture_recognizer/calculators:landmark_to_gesture_feature_calculator",
        "//jesturepipe/graphs/gesture_recognizer/calculators:gesture_recorder",
        "@mediapipe//mediapipe/calculators/core:begin_loop_calculator",
        "@mediapipe//mediapipe/calculators/core:end_loop_calculator",
    ],
)
