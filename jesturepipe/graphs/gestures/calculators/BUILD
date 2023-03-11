package(default_visibility = ["//visibility:public"])

cc_library(
    name = "gesture_frame_constructor_calculator",
    srcs = ["gesture_frame_constructor_calculator.cc"],
    deps = [
        "//jesturepipe/gesture",
        "//jesturepipe/gesture:frame_constructor",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/types:optional",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:node",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
    alwayslink = 1,
)

cc_library(
    name = "gesture_recognizer_calculator",
    srcs = ["gesture_recognizer_calculator.cc"],
    deps = [
        "//jesturepipe/gesture",
        "//jesturepipe/gesture:recognizer",
        "//jesturepipe/graphs/gestures:library_service",
        "@com_google_absl//absl/types:optional",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:node",
    ],
    alwayslink = 1,
)

cc_library(
    name = "gesture_recorder_calculator",
    srcs = ["gesture_recorder_calculator.cc"],
    deps = [
        "//jesturepipe/gesture",
        "//jesturepipe/gesture:recorder",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:node",
    ],
    alwayslink = 1,
)
