load(
    "@mediapipe//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

package(default_visibility = ["//visibility:public"])

exports_files(glob(["*.pbtxt"]))

mediapipe_simple_subgraph(
    name = "actions_graph",
    graph = "actions.pbtxt",
    register_as = "Actions",
    deps = [
        "//jesturepipe/graphs/actions/calculators:actions_calculator",
    ],
)
