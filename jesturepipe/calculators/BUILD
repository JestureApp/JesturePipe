package(default_visibility = ["//visibility:public"])

cc_library(
    name = "camera_calculator",
    srcs = [
        "camera_calculator.cc",
    ],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
        "@mediapipe//mediapipe/framework/port:opencv_video",
    ],
    alwayslink = 1,
)
