load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

exports_files(glob(["*.pbtxt"]))

mediapipe_simple_subgraph(
    name = "gesture_recognizer",
    graph = "gesture_recognizer.pbtxt",
    register_as = "GestureRecognizer",
)
