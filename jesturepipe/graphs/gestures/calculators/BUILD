package(default_visibility = ["//visibility:public"])

cc_library(
    name = "landmarks_to_hand_shape_calculator",
    srcs = ["landmarks_to_hand_shape_calculator.cc"],
    deps = [
        "//jesturepipe/gesture",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:node",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
    alwayslink = 1,
)
