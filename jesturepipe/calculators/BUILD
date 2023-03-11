package(default_visibility = ["//visibility:public"])

cc_library(
    name = "if_else_calculator",
    srcs = ["if_else_calculator.cc"],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:node",
        "@mediapipe//mediapipe/framework/api2:packet",
        "@mediapipe//mediapipe/util:header_util",
    ],
    alwayslink = 1,
)

cc_library(
    name = "camera_calculator",
    srcs = ["camera_calculator.cc"],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:node",
        "@mediapipe//mediapipe/framework/api2:packet",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
        "@mediapipe//mediapipe/framework/port:opencv_video",
    ],
    alwayslink = 1,
)

cc_library(
    name = "echoer_calculator",
    srcs = ["echoer_calculator.cc"],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
    ],
    alwayslink = 1,
)

cc_library(
    name = "get_vector_item_calculator",
    srcs = ["get_vector_item_calculator.cc"],
    deps = [
        "@mediapipe//mediapipe/calculators/core:get_vector_item_calculator",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
    alwayslink = 1,
)

cc_library(
    name = "optional_wrap_calculator",
    srcs = ["optional_wrap_calculator.cc"],
    hdrs = ["optional_wrap_calculator.h"],
    deps = [
        "@com_google_absl//absl/types:optional",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:node",
    ],
    alwayslink = 1,
)
