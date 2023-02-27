package(default_visibility = ["//visibility:public"])

cc_library(
    name = "gesture",
    srcs = ["gesture.cc"],
    hdrs = ["gesture.h"],
    deps = [
        "@com_google_absl//absl/hash",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
)

cc_library(
    name = "parser",
    srcs = ["parser.cc"],
    hdrs = ["parser.h"],
    deps = [
        ":gesture",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/types:optional",
        "@com_google_absl//absl/types:variant",
    ],
)
