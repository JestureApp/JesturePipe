# load("@bazel_skylib//rules:write_file.bzl", "write_file")
# load("@bazel_skylib//rules:diff_test.bzl", "diff_test")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "bindings",
    srcs = ["jesturepipe.cc"],
    hdrs = ["jesturepipe.h"],
    deps = [
        "//jesturepipe/graphs/jesturepipe",
        "@com_google_absl//absl/status",
        "@mediapipe//mediapipe/framework:calculator_framework",
    ],
)
