load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "hand_landmarks_calculators",
    deps = [
        "@mediapipe//mediapipe/calculators/core:gate_calculator",
        "@mediapipe//mediapipe/calculators/core:split_vector_calculator",
        "@mediapipe//mediapipe/calculators/tensor:image_to_tensor_calculator",
        "@mediapipe//mediapipe/calculators/tensor:inference_calculator",
        "@mediapipe//mediapipe/calculators/tensor:tensors_to_detections_calculator",
        "@mediapipe//mediapipe/calculators/tensor:tensors_to_classification_calculator",
        "@mediapipe//mediapipe/calculators/tensor:tensors_to_floats_calculator",
        "@mediapipe//mediapipe/calculators/tensor:tensors_to_landmarks_calculator",
        "@mediapipe//mediapipe/calculators/tflite:tflite_custom_op_resolver_calculator",
        "@mediapipe//mediapipe/calculators/tflite:tflite_model_calculator",
        "@mediapipe//mediapipe/calculators/tflite:ssd_anchors_calculator",
        "@mediapipe//mediapipe/calculators/util:local_file_contents_calculator",
        "@mediapipe//mediapipe/calculators/util:non_max_suppression_calculator",
        "@mediapipe//mediapipe/calculators/util:landmark_letterbox_removal_calculator",
        "@mediapipe//mediapipe/calculators/util:detection_letterbox_removal_calculator",
        "@mediapipe//mediapipe/calculators/util:landmark_projection_calculator",
        "@mediapipe//mediapipe/calculators/util:thresholding_calculator",
    ]
)

mediapipe_simple_subgraph(
    name = "model_loader_graph",
    graph = "model_loader.pbtxt",
    register_as = "ModelLoader",
    deps = [
        ":hand_landmarks_calculators",
    ],
)

mediapipe_simple_subgraph(
    name = "hand_landmark_detector_graph",
    graph = "hand_landmark_detector.pbtxt",
    register_as = "HandLandmarkDetector",
    deps = [
        ":model_loader_graph",
        ":hand_landmarks_calculators",
    ]
)

mediapipe_simple_subgraph(
    name = "palm_detector_graph",
    graph = "palm_detector.pbtxt",
    register_as = "PalmDetector",
    deps = [
        ":model_loader_graph",
        ":hand_landmarks_calculators",
    ]
)