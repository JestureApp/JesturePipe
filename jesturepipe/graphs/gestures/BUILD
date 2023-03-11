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
        ":landmarks_to_frames",
        "//jesturepipe/calculators:echoer_calculator",
        "//jesturepipe/graphs/hands",
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "landmarks_to_frames",
    graph = "landmarks_to_frames.pbtxt",
    register_as = "LandmarksToFrames",
    deps = [
        "//jesturepipe/calculators:echoer_calculator",
        "//jesturepipe/calculators:get_vector_item_calculator",
        "//jesturepipe/graphs/gestures/calculators:landmarks_to_hand_shape_calculator",
    ],
)
