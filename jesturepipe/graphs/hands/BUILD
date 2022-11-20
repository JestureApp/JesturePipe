load("//jesturepipe/tools:graphs.bzl", "jesture_binary_graph")

load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

exports_files(glob([
    "*.pbtxt",
]))

cc_library(
    name = "hands_calculators",
    deps = [
        "@mediapipe//mediapipe/calculators/core:clip_vector_size_calculator",
        "@mediapipe//mediapipe/calculators/core:begin_loop_calculator",
        "@mediapipe//mediapipe/calculators/core:end_loop_calculator",
        "@mediapipe//mediapipe/calculators/image:image_properties_calculator",
        "@mediapipe//mediapipe/modules/hand_landmark:palm_detection_detection_to_roi",
        "@mediapipe//mediapipe/calculators/util:annotation_overlay_calculator",
        "@mediapipe//mediapipe/calculators/util:landmarks_to_render_data_calculator",

        "//jesturepipe/graphs/hands/hand_landmarks:hand_landmarks_calculators",
    ]
)

mediapipe_simple_subgraph(
    name = "hands_renderer_graph",
    graph = "hands_renderer.pbtxt",
    register_as = "HandsRenderer",
    deps = [
        ":hands_calculators",
    ],
)

mediapipe_simple_subgraph(
    name = "hand_landmarks_graph",
    graph = "hand_landmarks.pbtxt",
    register_as = "HandLandmarks",
    deps = [
        "//jesturepipe/graphs/hands/hand_landmarks:hand_landmark_detector_graph",
        "//jesturepipe/graphs/hands/hand_landmarks:palm_detector_graph",

        ":hands_calculators",
    ]
)

jesture_binary_graph(
    name = "hands_demo_binary_graph",
    short_name = "hands_demo",
    graph = "hands_demo.pbtxt",
    deps = [
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
        
        ":hands_renderer_graph",
        ":hand_landmarks_graph",
        ":hands_calculators",
    ]
)
