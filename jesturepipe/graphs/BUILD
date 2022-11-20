load("@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_binary_graph")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "hands_demo",
    srcs = ["hands_demo.cc"],
    hdrs = ["hands_demo.h"],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/port:status",
        "@bazel_tools//tools/cpp/runfiles",
        
        "//jesturepipe/graphs/hands:hands_demo_binary_graph",
        "//jesturepipe/graphs/hands:hands_calculators",
    ],
    data = [
        "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_full.tflite",
        "@mediapipe//mediapipe/modules/palm_detection:palm_detection_full.tflite",
    ],
)