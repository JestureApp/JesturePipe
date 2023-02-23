"""
Setup for a workspace dependent on JesturePipe
"""

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
load("@org_tensorflow//tensorflow:workspace3.bzl", "tf_workspace3")
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
load("@actions//:repositories.bzl", "actions_repositories")

def jesturepipe_setup0():
    """
    Setup for a workspace dependent on JesturePipe
    """

    rules_foreign_cc_dependencies()
    protobuf_deps()
    tf_workspace3()
    actions_repositories()
