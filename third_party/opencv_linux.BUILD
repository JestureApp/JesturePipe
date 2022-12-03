cc_library(
    name = "opencv",
    # buildifier: disable=constant-globs
    hdrs = glob([
        "include/opencv4/opencv2/**/*.h*",
        "include/aarch64-linux-gnu/opencv4/opencv2/cvconfig.h",
        "include/arm-linux-gnueabihf/opencv4/opencv2/cvconfig.h",
        "include/x86_64-linux-gnu/opencv4/opencv2/cvconfig.h",
    ]),
    includes = [
        # For OpenCV 4.x
        "include/aarch64-linux-gnu/opencv4/",
        "include/arm-linux-gnueabihf/opencv4/",
        "include/x86_64-linux-gnu/opencv4/",
        "include/opencv4/",
    ],
    linkopts = [
        "-l:libopencv_core.so",
        "-l:libopencv_calib3d.so",
        "-l:libopencv_features2d.so",
        "-l:libopencv_highgui.so",
        "-l:libopencv_imgcodecs.so",
        "-l:libopencv_imgproc.so",
        "-l:libopencv_video.so",
        "-l:libopencv_videoio.so",
    ],
    visibility = ["//visibility:public"],
)
