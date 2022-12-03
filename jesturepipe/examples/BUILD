package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "hand_tracking",
    srcs = ["hand_tracking.cc"],
    deps = [
        "//jesturepipe/graphs/hands:hands_demo",
        "@com_google_absl//absl/flags:parse",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:opencv_highgui",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
        "@mediapipe//mediapipe/framework/port:opencv_video",
        "@mediapipe//mediapipe/framework/port:parse_text_proto",
        "@mediapipe//mediapipe/framework/port:status",
    ],
)

cc_binary(
    name = "jesturepipe_demo",
    srcs = ["jesturepipe_demo.cc"],
    deps = [
        "//jesturepipe/graphs/jesturepipe",
        "@com_google_absl//absl/status",
        "@mediapipe//mediapipe/framework:calculator_framework",
    ],
)
