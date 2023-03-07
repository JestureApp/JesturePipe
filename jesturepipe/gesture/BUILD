package(default_visibility = ["//visibility:public"])

cc_library(
    name = "gesture",
    srcs = ["gesture.cc"],
    hdrs = ["gesture.h"],
    deps = [
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
)

cc_library(
    name = "recognizer",
    srcs = ["recognizer.cc"],
    hdrs = ["recognizer.h"],
    deps = [
        ":gesture",
        "@com_google_absl//absl/types:optional",
        "@com_google_absl//absl/types:variant",
    ],
)

cc_library(
    name = "recorder",
    srcs = ["recorder.cc"],
    hdrs = ["recorder.h"],
    deps = [
        ":gesture",
    ],
)
