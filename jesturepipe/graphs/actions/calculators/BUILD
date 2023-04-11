package(default_visibility = ["//visibility:public"])

cc_library(
    name = "action_dispatcher_calculator",
    srcs = ["action_dispatcher_calculator.cc"],
    deps = [
        "//jesturepipe/actions:action",
        "//jesturepipe/actions:mapper",
        "@actions//actions",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:node",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
    alwayslink = 1,
)
