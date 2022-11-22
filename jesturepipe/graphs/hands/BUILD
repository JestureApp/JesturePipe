load("//jesturepipe/tools:graphs.bzl", "jesture_binary_graph")

load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

exports_files(glob([
    "*.pbtxt",
]))


mediapipe_simple_subgraph(
    name = "hands_renderer_graph",
    graph = "hands_renderer.pbtxt",
    register_as = "HandsRenderer",
    deps = [
        "@mediapipe//mediapipe/calculators/util:annotation_overlay_calculator",
        "@mediapipe//mediapipe/calculators/util:landmarks_to_render_data_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "model_loader_graph",
    graph = "model_loader.pbtxt",
    register_as = "ModelLoader",
    deps = [
        "@mediapipe//mediapipe/calculators/tflite:tflite_model_calculator",
        "@mediapipe//mediapipe/calculators/util:local_file_contents_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "hand_landmark_detector_graph",
    graph = "hand_landmark_detector.pbtxt",
    register_as = "HandLandmarkDetector",
    deps = [
        ":model_loader_graph",

        "@mediapipe//mediapipe/calculators/core:gate_calculator",
        "@mediapipe//mediapipe/calculators/core:split_vector_calculator",
        "@mediapipe//mediapipe/calculators/tensor:image_to_tensor_calculator",
        "@mediapipe//mediapipe/calculators/tensor:inference_calculator",
        "@mediapipe//mediapipe/calculators/tensor:tensors_to_landmarks_calculator",
        "@mediapipe//mediapipe/calculators/tensor:tensors_to_floats_calculator",
        "@mediapipe//mediapipe/calculators/util:thresholding_calculator",
        "@mediapipe//mediapipe/calculators/util:landmark_letterbox_removal_calculator",
        "@mediapipe//mediapipe/calculators/util:landmark_projection_calculator",
    ]
)

mediapipe_simple_subgraph(
    name = "palm_detector_graph",
    graph = "palm_detector.pbtxt",
    register_as = "PalmDetector",
    deps = [
        ":model_loader_graph",

        "@mediapipe//mediapipe/calculators/tensor:image_to_tensor_calculator",
        "@mediapipe//mediapipe/calculators/tensor:inference_calculator",
        "@mediapipe//mediapipe/calculators/tensor:tensors_to_detections_calculator",
        "@mediapipe//mediapipe/calculators/tflite:ssd_anchors_calculator",
        "@mediapipe//mediapipe/calculators/tflite:tflite_custom_op_resolver_calculator",
        "@mediapipe//mediapipe/calculators/util:non_max_suppression_calculator",
        "@mediapipe//mediapipe/calculators/util:detection_letterbox_removal_calculator",
    ]
)

mediapipe_simple_subgraph(
    name = "hands_graph",
    graph = "hands.pbtxt",
    register_as = "Hands",
    deps = [
        ":hand_landmark_detector_graph",
        ":palm_detector_graph",
        "@mediapipe//mediapipe/modules/hand_landmark:palm_detection_detection_to_roi",
        "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_landmarks_to_roi",

        "@mediapipe//mediapipe/calculators/core:clip_vector_size_calculator", 
        "@mediapipe//mediapipe/calculators/core:begin_loop_calculator", 
        "@mediapipe//mediapipe/calculators/core:end_loop_calculator", 
        "@mediapipe//mediapipe/calculators/core:previous_loopback_calculator",
        "@mediapipe//mediapipe/calculators/image:image_properties_calculator",
        "@mediapipe//mediapipe/calculators/util:association_calculator",
        "@mediapipe//mediapipe/calculators/util:association_norm_rect_calculator",
    ]
)

jesture_binary_graph(
    name = "hands_demo_binary_graph",
    short_name = "hands_demo",
    graph = "hands_demo.pbtxt",
    deps = [
        ":hands_renderer_graph",
        ":hands_graph",

        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
    ]
)

cc_library(
    name = "hands_demo",
    srcs = ["hands_demo.cc"],
    hdrs = ["hands_demo.h"],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/port:status",
        "@bazel_tools//tools/cpp/runfiles",
        
        "//jesturepipe/graphs/hands:hands_demo_binary_graph",
    ],
    data = [
        "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_full.tflite",
        "@mediapipe//mediapipe/modules/palm_detection:palm_detection_full.tflite",
    ],
)
