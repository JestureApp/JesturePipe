load("@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_binary_graph")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "hand_tracking_desktop_live",
    srcs = ["hand_tracking_desktop_live.cc"],
    hdrs = ["hand_tracking_desktop_live.h"],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/port:status",
        "//jesturepipe/graphs/hands:hands_binary_graph",
    ],
)