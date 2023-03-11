package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "gestures",
    srcs = ["gestures.cc"],
    deps = [
        "//jesturepipe/calculators:camera_calculator",
        "//jesturepipe/gesture:library",
        "//jesturepipe/graphs/gestures",
        "//jesturepipe/graphs/gestures:library_service",
        "//jesturepipe/graphs/util:frame_annotator",
        "@bazel_tools//tools/cpp/runfiles",
        "@com_google_absl//absl/status",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:builder",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:opencv_highgui",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
        "@mediapipe//mediapipe/framework/port:parse_text_proto",
    ],
)
