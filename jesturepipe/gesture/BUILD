package(default_visibility = ["//visibility:public"])

cc_library(
    name = "gesture",
    srcs = ["gesture.cc"],
    hdrs = ["gesture.h"],
    deps = [
        "@com_google_absl//absl/types:optional",
    ],
)

cc_library(
    name = "library",
    srcs = ["library.cc"],
    hdrs = ["library.h"],
    deps = [
        ":gesture",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/types:optional",
    ],
)

cc_library(
    name = "recognizer",
    srcs = ["recognizer.cc"],
    hdrs = ["recognizer.h"],
    deps = [
        ":gesture",
        ":library",
        "@com_google_absl//absl/types:optional",
        ":frame_count",
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

cc_library(
    name = "frame_constructor",
    srcs = ["frame_constructor.cc"],
    hdrs = ["frame_constructor.h"],
    deps = [
        ":gesture",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/types:optional",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
        ":frame_count",
    ],
)
cc_library(
    name = "frame_count",
    srcs = ["frame_count.cc"],
    hdrs = ["frame_count.h"],
    deps = [
        "@com_google_absl//absl/time",
    ],
)
