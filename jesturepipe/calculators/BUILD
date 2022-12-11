load("//jesturepipe/tools:models.bzl", "model_compile")

package(default_visibility = ["//visibility:public"])

# Note: every calculator must have alwayslink = 1 to be able to be used in graphs

cc_library(
    name = "camera_calculator",
    srcs = [
        "camera_calculator.cc",
    ],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
        "@mediapipe//mediapipe/framework/port:opencv_video",
    ],
    alwayslink = 1,
)

cc_library(
    name = "file_contents_or_path_calculator",
    srcs = [
        "file_contents_or_path_calculator.cc",
    ],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/util:resource_util",
    ],
    alwayslink = 1,
)

model_compile(
    name = "hand_landmark_lite",
    model = "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_full.tflite",
    var_name = "HAND_LANDMARK_LITE_MODEL",
)

cc_library(
    name = "hand_landmark_model_lite_calculator",
    srcs = [
        "hand_landmark_model_lite_calculator.cc",
    ],
    deps = [
        ":hand_landmark_lite",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/util/tflite:tflite_model_loader",
        "@org_tensorflow//tensorflow/lite:framework",
    ],
    alwayslink = 1,
)

model_compile(
    name = "palm_detection_lite",
    model = "@mediapipe//mediapipe/modules/palm_detection:palm_detection_lite.tflite",
    var_name = "PALM_DETECTION_LITE_MODEL",
)

cc_library(
    name = "palm_detection_model_lite_calculator",
    srcs = [
        "palm_detection_model_lite_calculator.cc",
    ],
    deps = [
        ":palm_detection_lite",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/util/tflite:tflite_model_loader",
        "@org_tensorflow//tensorflow/lite:framework",
    ],
    alwayslink = 1,
)
