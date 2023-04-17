# JesturePipe
JesturePipe is the backend pipeline for the Jesture application. 

## Prerequisites
* OpenCV

## Bazel Workspace Setup
```starlark
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "jesturepipe",
    strip_prefix = "JesturePipe-1.0.0",
    url = "https://github.com/JestureApp/JesturePipe/archive/refs/tags/v1.0.0.zip",
)

load("@jesturepipe//:repositories.bzl", "jesturepipe_repositories")

jesturepipe_repositories()

# SETUP STAGE 1
load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
load("@org_tensorflow//tensorflow:workspace3.bzl", "tf_workspace3")
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
load("@actions//:repositories.bzl", "actions_repositories")

rules_foreign_cc_dependencies()

protobuf_deps()

tf_workspace3()

actions_repositories()

# SETUP SAGE 2
load("@actions//display:display_configure.bzl", "display_configure")

display_configure()

# SETUP SAGE 3
load("@org_tensorflow//tensorflow:workspace2.bzl", "tf_workspace2")
load("@display//:local_display.bzl", "display_repositories")

tf_workspace2()

display_repositories()
```

## Contributing
See [Contributing](Contributing.md) for instructions on contributing.