load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

mediapipe_simple_subgraph(
    name = "gestures",
    graph = "gestures.pbtxt",
    register_as = "Gestures",
    deps = [
        "//jesturepipe/calculators:echoer_calculator",
        "//jesturepipe/calculators:get_vector_item_calculator",
        "//jesturepipe/calculators:state_change_calculator",
        "//jesturepipe/graphs/gestures/calculators:gesture_frame_constructor_calculator",
        "//jesturepipe/graphs/gestures/calculators:gesture_recognizer_calculator",
        "//jesturepipe/graphs/gestures/calculators:gesture_recorder_calculator",
        "//jesturepipe/graphs/hands",
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
        "@mediapipe//mediapipe/calculators/core:flow_limiter_calculator",
        "@mediapipe//mediapipe/calculators/core:gate_calculator",
        "@mediapipe//mediapipe/calculators/core:merge_calculator",
        "@mediapipe//mediapipe/calculators/core:packet_cloner_calculator",
        "@mediapipe//mediapipe/calculators/util:clock_timestamp_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "is_recording_latch",
    graph = "is_recording_latch.pbtxt",
    register_as = "IsRecordingLatch",
    deps = [
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
        "@mediapipe//mediapipe/calculators/core:merge_calculator",
        "@mediapipe//mediapipe/calculators/core:packet_cloner_calculator",
        "@mediapipe//mediapipe/calculators/core:packet_sequencer_calculator",
        "@mediapipe//mediapipe/calculators/core:side_packet_to_stream_calculator",
    ],
)
