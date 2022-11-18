load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_binary_graph",
)

package(default_visibility = ["//visibility:public"])

# mediapipe_binary_graph(
#     name = "hand_tracking_desktop_live",
#     graph = 
# )

cc_binary(
    name = "hand_tracking",
    srcs = ["hand_tracking.cc"],
    deps = [
        "//jesturepipe/graphs:hand_tracking_desktop_live",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/port:parse_text_proto",
        "@mediapipe//mediapipe/framework/port:status",
        "@mediapipe//mediapipe/framework/port:opencv_highgui",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
        "@mediapipe//mediapipe/framework/port:opencv_video",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@com_google_absl//absl/flags:parse",
    ]
)