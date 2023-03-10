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
    name = "fps_to_render_data_calculator",
    srcs = ["fps_to_render_data_calculator.cc"],
    deps = [
        "@com_google_absl//absl/strings:str_format",
        "@mediapipe//mediapipe/calculators/util:packet_frequency_cc_proto",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:node",
        "@mediapipe//mediapipe/framework/api2:packet",
        "@mediapipe//mediapipe/util:color_cc_proto",
        "@mediapipe//mediapipe/util:render_data_cc_proto",
    ],
    alwayslink = 1,
)
