load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

mediapipe_simple_subgraph(
    name = "model_loader",
    graph = "model_loader.pbtxt",
    register_as = "ModelLoader",
    deps = [
        "@mediapipe//mediapipe/calculators/tflite:tflite_model_calculator",
        "@mediapipe//mediapipe/calculators/util:local_file_contents_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "palm_detector",
    data = [
        "@mediapipe//mediapipe/modules/palm_detection:palm_detection_full.tflite",
        "@mediapipe//mediapipe/modules/palm_detection:palm_detection_lite.tflite",
    ],
    graph = "palm_detector.pbtxt",
    register_as = "PalmDetector",
    deps = [
        ":model_loader",
        "@mediapipe//mediapipe/calculators/tensor:image_to_tensor_calculator",
        "@mediapipe//mediapipe/calculators/tensor:inference_calculator",
        "@mediapipe//mediapipe/calculators/tensor:tensors_to_detections_calculator",
        "@mediapipe//mediapipe/calculators/tflite:ssd_anchors_calculator",
        "@mediapipe//mediapipe/calculators/tflite:tflite_custom_op_resolver_calculator",
        "@mediapipe//mediapipe/calculators/util:detection_letterbox_removal_calculator",
        "@mediapipe//mediapipe/calculators/util:non_max_suppression_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "hand_landmark_detector",
    data = [
        "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_full.tflite",
        "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_lite.tflite",
    ],
    graph = "hand_landmark_detector.pbtxt",
    register_as = "HandLandmarkDetector",
    deps = [
        ":model_loader",
        "@mediapipe//mediapipe/calculators/core:gate_calculator",
        "@mediapipe//mediapipe/calculators/core:split_vector_calculator",
        "@mediapipe//mediapipe/calculators/tensor:image_to_tensor_calculator",
        "@mediapipe//mediapipe/calculators/tensor:inference_calculator",
        "@mediapipe//mediapipe/calculators/tensor:tensors_to_classification_calculator",
        "@mediapipe//mediapipe/calculators/tensor:tensors_to_floats_calculator",
        "@mediapipe//mediapipe/calculators/tensor:tensors_to_landmarks_calculator",
        "@mediapipe//mediapipe/calculators/util:landmark_letterbox_removal_calculator",
        "@mediapipe//mediapipe/calculators/util:landmark_projection_calculator",
        "@mediapipe//mediapipe/calculators/util:thresholding_calculator",
        "@mediapipe//mediapipe/calculators/util:world_landmark_projection_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "hands",
    graph = "hands.pbtxt",
    register_as = "Hands",
    deps = [
        ":hand_landmark_detector",
        ":palm_detector",
        "//jesturepipe/calculators:if_else_calculator",
        "@mediapipe//mediapipe/calculators/core:begin_loop_calculator",
        "@mediapipe//mediapipe/calculators/core:clip_vector_size_calculator",
        "@mediapipe//mediapipe/calculators/core:end_loop_calculator",
        "@mediapipe//mediapipe/calculators/core:gate_calculator",
        "@mediapipe//mediapipe/calculators/core:previous_loopback_calculator",
        "@mediapipe//mediapipe/calculators/image:image_properties_calculator",
        "@mediapipe//mediapipe/calculators/util:association_norm_rect_calculator",
        "@mediapipe//mediapipe/calculators/util:collection_has_min_size_calculator",
        "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_landmarks_to_roi",
        "@mediapipe//mediapipe/modules/hand_landmark:palm_detection_detection_to_roi",
    ],
)

mediapipe_simple_subgraph(
    name = "hands_renderer",
    graph = "hands_renderer.pbtxt",
    register_as = "HandsRenderer",
    deps = [
        "@mediapipe//mediapipe/calculators/core:begin_loop_calculator",
        "@mediapipe//mediapipe/calculators/core:end_loop_calculator",
        "@mediapipe//mediapipe/calculators/util:annotation_overlay_calculator",
        "@mediapipe//mediapipe/calculators/util:landmarks_to_render_data_calculator",
    ],
)
