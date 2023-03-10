load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

mediapipe_simple_subgraph(
    name = "frame_annotator",
    graph = "frame_annotator.pbtxt",
    register_as = "FrameAnnotator",
    deps = [
        "@mediapipe//mediapipe/calculators/core:begin_loop_calculator",
        "@mediapipe//mediapipe/calculators/core:end_loop_calculator",
        "@mediapipe//mediapipe/calculators/util:annotation_overlay_calculator",
        "@mediapipe//mediapipe/calculators/util:landmarks_to_render_data_calculator",
    ],
)
