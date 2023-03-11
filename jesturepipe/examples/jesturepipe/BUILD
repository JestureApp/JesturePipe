package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "jesturepipe",
    srcs = ["jesturepipe.cc"],
    deps = [
        "//jesturepipe",
        "//jesturepipe/graphs/gestures",
        "@bazel_tools//tools/cpp/runfiles",
        "@com_google_absl//absl/status",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:opencv_highgui",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
    ],
)
