package(default_visibility = ["//visibility:public"])

cc_library(
    name = "jesturepipe",
    srcs = ["jesturepipe.cc"],
    hdrs = ["jesturepipe.h"],
    deps = [
        "//jesturepipe/actions:mapper",
        # "//jesturepipe/calculators:camera_calculator",
        "//jesturepipe/gesture",
        "//jesturepipe/gesture:library",
        "//jesturepipe/graphs/actions",
        "//jesturepipe/graphs/gestures",
        "//jesturepipe/graphs/gestures:is_recording_latch",
        # "//jesturepipe/graphs/util:frame_annotator",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/api2:builder",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
        "@mediapipe//mediapipe/framework/port:parse_text_proto",
    ],
)
