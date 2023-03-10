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
    ],
)
