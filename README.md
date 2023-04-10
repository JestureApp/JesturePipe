# Jesture Pipe

## Bazel Workspace Setup
```starlark
load("//:repositories.bzl", "jesturepipe_repositories")

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
load("@org_tensorflow//tensorflow:workspace2.bzl", "tf_workspace2")

tf_workspace2()
```

## Contributing
See [Contributing](Contributing.md) for instructions on contributing.