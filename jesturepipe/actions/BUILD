package(default_visibility = ["//visibility:public"])

cc_library(
    name = "mapper",
    hdrs = ["mapper.h"],
    deps = [
        ":action",
        "@com_google_absl//absl/container:flat_hash_map",
    ],
)

cc_library(
    name = "action",
    hdrs = ["action.h"],
    deps = [
        "@actions//actions:action",
        "@com_google_absl//absl/types:variant",
    ],
)
