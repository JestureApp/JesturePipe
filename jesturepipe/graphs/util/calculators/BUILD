package(default_visibility = ["//visibility:public"])

cc_library(
    name = "debug_render_data_calculator",
    srcs = ["debug_render_data_calculator.cc"],
    deps = [
        "//jesturepipe/gesture",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/types:optional",
        "@mediapipe//mediapipe/calculators/util:packet_frequency_cc_proto",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:node",
        "@mediapipe//mediapipe/framework/api2:packet",
        "@mediapipe//mediapipe/util:color_cc_proto",
        "@mediapipe//mediapipe/util:render_data_cc_proto",
    ],
    alwayslink = 1,
)
