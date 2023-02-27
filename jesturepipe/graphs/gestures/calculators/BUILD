package(default_visibility = ["//visibility:public"])

cc_library(
    name = "landmark_to_gesture_frame_calculator",
    srcs = ["landmark_to_gesture_frame_calculator.cc"],
    deps = [
        "//jesturepipe/gesture",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/types:optional",
        "@mediapipe//mediapipe/framework:calculator_framework",
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
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/types:optional",
        "@mediapipe//mediapipe/framework:calculator_framework",
    ],
    alwayslink = 1,
)

cc_library(
    name = "calc_ext",
    srcs = ["calc_ext.cc"],
    deps = [
        "//jesturepipe/calculators:dedup_calculator",
        "//jesturepipe/gesture",
        "@com_google_absl//absl/types:optional",
        "@mediapipe//mediapipe/calculators/core:begin_loop_calculator",
        "@mediapipe//mediapipe/calculators/core:end_loop_calculator",
        "@mediapipe//mediapipe/calculators/core:get_vector_item_calculator",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
    alwayslink = 1,
)
