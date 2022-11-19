# load("@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl", 
#     "mediapipe_binary_graph",
#     "data_as_c_string")

load("//jesturepipe/tools:graphs.bzl", "jesture_binary_graph")

package(default_visibility = ["//visibility:public"])

exports_files(glob([
    "*.pbtxt",
]))

cc_library(
    name = "hands_calculators",
    deps = [
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
        "@mediapipe//mediapipe/graphs/hand_tracking/subgraphs:hand_renderer_cpu",

        "//jesturepipe/graphs/hands/subgraphs:hand_tracking_graph",
    ]
)

jesture_binary_graph(
    name = "hands_binary_graph",
    short_name = "graph_hands",
    graph = "hands.pbtxt",
    deps = [":hands_calculators"],
)