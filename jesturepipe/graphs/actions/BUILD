load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

mediapipe_simple_subgraph(
    name = "actions",
    graph = "actions.pbtxt",
    register_as = "Actions",
    deps = [
        "//jesturepipe/calculators:get_vector_item_calculator",
        "//jesturepipe/graphs/actions/calculators:action_dispatcher_calculator",
    ],
)
