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
    name = "if_else_calculator",
    srcs = [
        "if_else_calculator.cc",
    ],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/util:header_util",
    ],
    alwayslink = 1,
)

cc_library(
    name = "echoer_calculator",
    srcs = ["echoer_calculator.cc"],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/util:header_util",
    ],
    alwayslink = 1,
)

cc_library(
    name = "optional_calculator",
    srcs = ["optional_calculator.cc"],
    hdrs = ["optional_calculator.h"],
    deps = [
        "@com_google_absl//absl/types:optional",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
    alwayslink = 1,
)

cc_library(
    name = "fixed_length_vector_calculator",
    srcs = ["fixed_length_vector_calculator.cc"],
    hdrs = ["fixed_length_vector_calculator.h"],
    deps = [
        "@com_google_absl//absl/types:optional",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
        "@mediapipe//mediapipe/framework/port:logging",
    ],
    alwayslink = 1,
)

cc_library(
    name = "dedup_calculator",
    hdrs = ["dedup_calculator.h"],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
    ],
)
