load("//jesturepipe/tools:graphs.bzl", "jesture_binary_graph")

package(default_visibility = ["//visibility:public"])

exports_files(glob([
    "*.pbtxt",
]))

jesture_binary_graph(
    name = "jesturepipe_binary_graph",
    graph = "jesturepipe.pbtxt",
    short_name = "jesturepipe",
    deps = [
        "//jesturepipe/calculators:camera_calculator",
        "//jesturepipe/calculators:echoer_calculator",
        "//jesturepipe/graphs/gestures:gestures_graph",
        "//jesturepipe/graphs/hands:hands_graph",
        "//jesturepipe/graphs/hands:hands_renderer_graph",
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
        "@mediapipe//mediapipe/calculators/core:merge_calculator",
        "@mediapipe//mediapipe/calculators/core:packet_cloner_calculator",
        "@mediapipe//mediapipe/calculators/core:packet_sequencer_calculator",
        "@mediapipe//mediapipe/calculators/core:side_packet_to_stream_calculator",
        "@mediapipe//mediapipe/framework:calculator_framework",
    ],
)

cc_library(
    name = "jesturepipe",
    srcs = ["jesturepipe.cc"],
    hdrs = ["jesturepipe.h"],
    deps = [
        ":jesturepipe_binary_graph",
        "@com_google_absl//absl/status",
        "@mediapipe//mediapipe/framework:calculator_framework",
    ],
)
