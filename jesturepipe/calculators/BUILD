package(default_visibility = ["//visibility:public"])

# Note: every calculator must have alwayslink = 1 to be able to be used in graphs

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

cc_library(
    name = "dedup_calculator",
    srcs = [
        "dedup_calculator.cc",
    ],
    hdrs = [
        "dedup_calculator.h",
    ],
)
