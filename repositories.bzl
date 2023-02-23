""" 
Dependency management 
"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

deps_remote_repositories = {
    # "org_tensorflow": {
    #     "url": "https://github.com/tensorflow/tensorflow/archive/refs/tags/v2.10.1.tar.gz",
    #     "sha256": "622a92e22e6f3f4300ea43b3025a0b6122f1cc0e2d9233235e4c628c331a94a3",
    #     "strip_prefix": "tensorflow-2.10.1",
    #     "patches": [
    #         "//third_party:org_tensorflow_custom_ops.diff",
    #     ],
    #     "patch_args": [
    #         "-p1",
    #     ],
    # },
    # "com_google_protobuf": {
    #     "url": "https://github.com/protocolbuffers/protobuf/archive/refs/tags/v21.9.tar.gz",
    #     "sha256": "0aa7df8289c957a4c54cbe694fbabe99b180e64ca0f8fdb5e2f76dcf56ff2422",
    #     "strip_prefix": "protobuf-21.9",
    # },
    # "io_bazel_rules_closure": {
    #     "urls": [
    #         "http://mirror.tensorflow.org/github.com/bazelbuild/rules_closure/archive/cf1e44edb908e9616030cc83d085989b8e6cd6df.tar.gz",
    #         "https://github.com/bazelbuild/rules_closure/archive/cf1e44edb908e9616030cc83d085989b8e6cd6df.tar.gz",  # 2019-04-04
    #     ],
    #     "sha256": "e0a111000aeed2051f29fcc7a3f83be3ad8c6c93c186e64beb1ad313f0c7f9f9",
    #     "strip_prefix": "rules_closure-cf1e44edb908e9616030cc83d085989b8e6cd6df",
    # },
    # "bazel_skylib": {
    #     "urls": [
    #         "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
    #         "https://github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
    #     ],
    #     "sha256": "74d544d96f4a5bb630d465ca8bbcfe231e3594e5aae57e1edbf17a6eb3ca2506",
    # },
    # "mediapipe": {
    #     "url": "https://github.com/google/mediapipe/archive/refs/tags/v0.8.11.zip",
    #     "sha256": "29276f31a6255b3afd27c2ceee63d39be46623ec01658973e305e95acc712eb4",
    #     "strip_prefix": "mediapipe-0.8.11",
    #     "patches": [
    #         "//third_party:mediapipe_macos.diff",
    #     ],
    #     "patch_args": [
    #         "-p1",
    #     ],
    # },
    # "build_bazel_rules_android": {
    #     "url": "https://github.com/bazelbuild/rules_android/archive/v0.1.1.zip",
    #     "sha256": "cd06d15dd8bb59926e4d65f9003bfc20f9da4b2519985c27e190cddc8b7a7806",
    #     "strip_prefix": "rules_android-0.1.1",
    # },
    # "rules_foreign_cc": {
    #     "url": "https://github.com/bazelbuild/rules_foreign_cc/archive/0.1.0.zip",
    #     "strip_prefix": "rules_foreign_cc-0.1.0",
    # },
    # "com_github_glog_glog": {
    #     "url": "https://github.com/google/glog/archive/v0.6.0.zip",
    #     "sha256": "122fb6b712808ef43fbf80f75c52a21c9760683dae470154f02bddfc61135022",
    #     "strip_prefix": "glog-0.6.0",
    # },
    "com_github_gflags_gflags": {
        "url": "https://github.com/gflags/gflags/archive/v2.2.2.tar.gz",
        "sha256": "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
        "strip_prefix": "gflags-2.2.2",
    },
    "com_google_googletest": {
        "url": "https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz",
        "strip_prefix": "googletest-release-1.12.1",
    },
    # "rules_rust": {
    #     "sha256": "dd79bd4e2e2adabae738c5e93c36d351cf18071ff2acf6590190acf4138984f6",
    #     "urls": ["https://github.com/bazelbuild/rules_rust/releases/download/0.14.0/rules_rust-v0.14.0.tar.gz"],
    # },
}

deps_remote_files = {
    # "com_google_mediapipe_hand_landmark_full_tflite": {
    #     "url": "https://storage.googleapis.com/mediapipe-assets/hand_landmark_full.tflite?generation=1661875760968579",
    #     "sha256": "11c272b891e1a99ab034208e23937a8008388cf11ed2a9d776ed3d01d0ba00e3",
    # },
    # "com_google_mediapipe_hand_landmark_lite_tflite": {
    #     "url": "https://storage.googleapis.com/mediapipe-assets/hand_landmark_lite.tflite?generation=1661875766398729",
    #     "sha256": "048edd3645c9bf7397d19a9f6e3a42957d6e414c9bea6598030a2e9b624156e6",
    # },
    # "com_google_mediapipe_palm_detection_full_tflite": {
    #     "url": "https://storage.googleapis.com/mediapipe-assets/palm_detection_full.tflite?generation=1662745358034050",
    #     "sha256": "1b14e9422c6ad006cde6581a46c8b90dd573c07ab7f3934b5589e7cea3f89a54",
    # },
    "com_google_mediapipe_palm_detection_lite_tflite": {
        "url": "https://storage.googleapis.com/mediapipe-assets/palm_detection_lite.tflite?generation=1661875885885770",
        "sha256": "e9a4aaddf90dda56a87235303cf00e4c2d3fb28725f68fd88772997dac905c18",
    },
}

def jesturepipe_repositories():
    """Loads all dependencies for jesture."""

    maybe(
        http_archive,
        name = "org_tensorflow",
        url = "https://github.com/tensorflow/tensorflow/archive/refs/tags/v2.10.1.tar.gz",
        sha256 = "622a92e22e6f3f4300ea43b3025a0b6122f1cc0e2d9233235e4c628c331a94a3",
        strip_prefix = "tensorflow-2.10.1",
        patches = [
            "@jesturepipe//third_party:org_tensorflow_custom_ops.diff",
        ],
        patch_args = [
            "-p1",
        ],
    )

    maybe(
        http_archive,
        name = "com_google_protobuf",
        url = "https://github.com/protocolbuffers/protobuf/archive/refs/tags/v21.9.tar.gz",
        sha256 = "0aa7df8289c957a4c54cbe694fbabe99b180e64ca0f8fdb5e2f76dcf56ff2422",
        strip_prefix = "protobuf-21.9",
    )

    maybe(
        http_archive,
        name = "io_bazel_rules_closure",
        urls = [
            "http://mirror.tensorflow.org/github.com/bazelbuild/rules_closure/archive/cf1e44edb908e9616030cc83d085989b8e6cd6df.tar.gz",
            "https://github.com/bazelbuild/rules_closure/archive/cf1e44edb908e9616030cc83d085989b8e6cd6df.tar.gz",  # 2019-04-04
        ],
        sha256 = "e0a111000aeed2051f29fcc7a3f83be3ad8c6c93c186e64beb1ad313f0c7f9f9",
        strip_prefix = "rules_closure-cf1e44edb908e9616030cc83d085989b8e6cd6df",
    )

    maybe(
        http_archive,
        name = "bazel_skylib",
        urls = [
            "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
            "https://github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
        ],
        sha256 = "74d544d96f4a5bb630d465ca8bbcfe231e3594e5aae57e1edbf17a6eb3ca2506",
    )

    maybe(
        http_archive,
        name = "mediapipe",
        url = "https://github.com/google/mediapipe/archive/refs/tags/v0.8.11.zip",
        sha256 = "29276f31a6255b3afd27c2ceee63d39be46623ec01658973e305e95acc712eb4",
        strip_prefix = "mediapipe-0.8.11",
        patches = [
            "@jesturepipe//third_party:mediapipe_macos.diff",
        ],
        patch_args = [
            "-p1",
        ],
    )

    maybe(
        http_archive,
        name = "rules_foreign_cc",
        url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.1.0.zip",
        strip_prefix = "rules_foreign_cc-0.1.0",
        sha256 = "c2cdcf55ffaf49366725639e45dedd449b8c3fe22b54e31625eb80ce3a240f1e",
    )

    maybe(
        http_archive,
        name = "com_github_glog_glog",
        url = "https://github.com/google/glog/archive/v0.6.0.zip",
        sha256 = "122fb6b712808ef43fbf80f75c52a21c9760683dae470154f02bddfc61135022",
        strip_prefix = "glog-0.6.0",
    )

    # maybe(
    #     http_archive,
    #     name = "build_bazel_rules_android",
    #     url = "https://github.com/bazelbuild/rules_android/archive/v0.1.1.zip",
    #     sha256 = "cd06d15dd8bb59926e4d65f9003bfc20f9da4b2519985c27e190cddc8b7a7806",
    #     strip_prefix = "rules_android-0.1.1",
    # )

    maybe(
        http_file,
        name = "com_google_mediapipe_hand_landmark_full_tflite",
        url = "https://storage.googleapis.com/mediapipe-assets/hand_landmark_full.tflite?generation=1661875760968579",
        sha256 = "11c272b891e1a99ab034208e23937a8008388cf11ed2a9d776ed3d01d0ba00e3",
    )

    maybe(
        http_file,
        name = "com_google_mediapipe_hand_landmark_lite_tflite",
        url = "https://storage.googleapis.com/mediapipe-assets/hand_landmark_lite.tflite?generation=1661875766398729",
        sha256 = "048edd3645c9bf7397d19a9f6e3a42957d6e414c9bea6598030a2e9b624156e6",
    )

    maybe(
        http_file,
        name = "com_google_mediapipe_palm_detection_full_tflite",
        url = "https://storage.googleapis.com/mediapipe-assets/palm_detection_full.tflite?generation=1662745358034050",
        sha256 = "1b14e9422c6ad006cde6581a46c8b90dd573c07ab7f3934b5589e7cea3f89a54",
    )

    maybe(
        http_file,
        name = "com_google_mediapipe_palm_detection_lite_tflite",
        url = "https://storage.googleapis.com/mediapipe-assets/palm_detection_lite.tflite?generation=1661875885885770",
        sha256 = "e9a4aaddf90dda56a87235303cf00e4c2d3fb28725f68fd88772997dac905c18",
    )

    maybe(
        native.new_local_repository,
        name = "linux_opencv",
        build_file = "@jesturepipe//third_party:opencv_linux.BUILD",
        path = "/usr",
    )

    maybe(
        native.new_local_repository,
        name = "macos_opencv",
        build_file = "@jesturepipe//third_party:opencv_macos.BUILD",
        path = "/opt/homebrew",
    )

    maybe(
        git_repository,
        name = "actions",
        remote = "git@capstone-cs.eng.utah.edu:jesture/actions.git",
        tag = "v0.1.1",
    )
