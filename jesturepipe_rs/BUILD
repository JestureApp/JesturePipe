load("@rules_rust//rust:defs.bzl", "rust_binary", "rust_library", "rust_test")

rust_library(
    name = "jesturepipe_rs",
    srcs = glob(["src/**/*.rs"]),
    deps = [
        "//jesturepipe_rs/bindings",
    ],
)

rust_test(
    name = "jesturepipe_rs_test",
    crate = ":jesturepipe_rs",
    data = [
        "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_lite.tflite",
        "@mediapipe//mediapipe/modules/palm_detection:palm_detection_lite.tflite",
    ],
    # env = {
    #     "HAND_MODEL_PATH": "$(execpath @mediapipe//mediapipe/modules/hand_landmark:hand_landmark_lite.tflite)",
    #     "PALM_MODEL_PATH": "$(execpath @mediapipe//mediapipe/modules/palm_detection:palm_detection_lite.tflite)",
    # },
    # rustc_env = {
    #     "HAND_MODEL_PATH": "$(execpath @mediapipe//mediapipe/modules/hand_landmark:hand_landmark_lite.tflite)",
    #     "PALM_MODEL_PATH": "$(execpath @mediapipe//mediapipe/modules/palm_detection:palm_detection_lite.tflite)",
    # },
    deps = [
        "@mediapipe//mediapipe/framework/port:opencv_core",
        "@rules_rust//tools/runfiles",
    ],
)

rust_binary(
    name = "demo",
    srcs = ["examples/demo.rs"],
    data = [
        "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_lite.tflite",
        "@mediapipe//mediapipe/modules/palm_detection:palm_detection_lite.tflite",
    ],
    deps = [
        ":jesturepipe_rs",
        "@mediapipe//mediapipe/framework/port:opencv_core",
        "@rules_rust//tools/runfiles",
    ],
)
