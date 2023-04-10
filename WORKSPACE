workspace(name = "jesturepipe")

################################################################################
# Development Dependencies
################################################################################

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "bazel_skylib",
    sha256 = "74d544d96f4a5bb630d465ca8bbcfe231e3594e5aae57e1edbf17a6eb3ca2506",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
    ],
)

# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",
    sha256 = "085bde6c5212c8c1603595341ffe7133108034808d8c819f8978b2b303afc9e7",
    strip_prefix = "bazel-compile-commands-extractor-ed994039a951b736091776d677f324b3903ef939",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/ed994039a951b736091776d677f324b3903ef939.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()

################################################################################
# Workspace Setup
################################################################################

# new_local_repository(
#     name = "macos_opencv",
#     build_file = "@jesturepipe//third_party:opencv_macos.BUILD",
#     path = "/usr/local",
# )

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

load("@bazel_skylib//lib:versions.bzl", "versions")

versions.check(
    maximum_bazel_version = "5.3.0",
    minimum_bazel_version = "5.0.0",
)

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
