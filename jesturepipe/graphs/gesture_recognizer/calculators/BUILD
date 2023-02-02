package(default_visibility = ["//visibility:public"])

cc_library(
    name = "gesture",
    hdrs = [
        "gesture.h",
    ],
)

cc_library(
    name = "gesture_store",
    hdrs = ["gesture_store.h"],
    srcs = ["gesture_store.cc"],
    deps = [
        ":gesture",
    ],
)

cc_library(
    name = "landmark_to_gesture_feature_calculator",
    srcs = [
        "landmark_to_gesture_feature_calculator.cc",
    ],
    deps = [
        ":gesture",
        ":gesture_store",
        "@com_google_absl//absl/status",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
    alwayslink = 1,
)

cc_library(
    name = "gesture_recorder",
    srcs = [
        "gesture_recorder.cc",
    ],
    deps = [
        ":gesture",
        ":gesture_store",
        "@com_google_absl//absl/status",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
    alwayslink = 1,
)

cc_library(
    name = "gesture_classifier_calculator",
    srcs = [
        "gesture_classifier_calculator.cc",
    ],
    deps = [
        ":gesture",
        ":gesture_store",
        "@com_google_absl//absl/status",
        "@mediapipe//mediapipe/framework:calculator_framework",
    ],
    alwayslink = 1,
)
