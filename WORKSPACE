
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
    name = "bazel_skylib",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
    ],
    sha256 = "74d544d96f4a5bb630d465ca8bbcfe231e3594e5aae57e1edbf17a6eb3ca2506",
)
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
bazel_skylib_workspace()

load("@bazel_skylib//lib:versions.bzl", "versions")
versions.check(minimum_bazel_version = "5.0.0")

load("//:deps.bzl", "jesturepipe_respositories")
jesturepipe_respositories()

# Necessary to break these up or else tensorflow setup will fail
load("@org_tensorflow//tensorflow:workspace3.bzl", "tf_workspace3")
load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
tf_workspace3()

rules_foreign_cc_dependencies()

load("@org_tensorflow//tensorflow:workspace2.bzl", "tf_workspace2")
tf_workspace2()

# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",

    # Replace the commit hash in both places (below) with the latest, rather than using the stale one here.
    # Even better, set up Renovate and let it do the work for you (see "Suggestion: Updates" in the README).
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/c200ce8b3e0baa04fa5cc3fb222260c9ea06541f.tar.gz",
    strip_prefix = "bazel-compile-commands-extractor-c200ce8b3e0baa04fa5cc3fb222260c9ea06541f",
    # When you first run this tool, it'll recommend a sha256 hash to put here with a message like: "DEBUG: Rule 'hedron_compile_commands' indicated that a canonical reproducible form can be obtained by modifying arguments sha256 = ..."
    sha256 = "b0a8af42e06108ec62382703daf27f7d8d247fd1b930f249045c70cd9d22f72e",
)
load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")
hedron_compile_commands_setup()
