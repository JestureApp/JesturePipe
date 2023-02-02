cc_library(
    name = "X11",
    # buildifier: disable=constant-globs
    hdrs = glob([
        "include/X11/**/*.h*",
    ]),
    includes = [
        "include/X11/",
    ],
    linkopts = [
        "-l:libX11.so",
    ],
    visibility = ["//visibility:public"],
)
