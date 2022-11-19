load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

exports_files(glob([
    "*.pbtxt",
]))

cc_library(
    name = "hand_tracking_calculators",
    deps = [
        "@mediapipe//mediapipe/calculators/util:association_calculator",
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
        "@mediapipe//mediapipe/calculators/tflite:tflite_model_calculator",
        "@mediapipe//mediapipe/calculators/util:local_file_contents_calculator",
        "@mediapipe//mediapipe/framework/tool:switch_container",
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
    ]
)

mediapipe_simple_subgraph(
    name = "hand_tracking_graph",
    graph = "hand_tracking.pbtxt",
    register_as = "HandTrackingGraph",
    deps = [
        ":hand_tracking_calculators",
    ],
)