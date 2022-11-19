load("@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl","mediapipe_binary_graph")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "hand_tracking_desktop_live",
    srcs = ["hand_tracking_desktop_live.cc"],
    hdrs = ["hand_tracking_desktop_live.h"],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/port:status",
        "@mediapipe//mediapipe/framework/port:file_helpers",
        "@mediapipe//mediapipe/graphs/hand_tracking:desktop_tflite_calculators",
        "@bazel_tools//tools/cpp/runfiles",
    ],
    data = [
        "@mediapipe//mediapipe/graphs/hand_tracking:hand_tracking_desktop_live_binary_graph",
    ],
)