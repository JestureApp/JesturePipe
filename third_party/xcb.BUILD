cc_import(
    name = "xcb",
    shared_library = "lib/libxcb.so",
    hdrs = glob(["include/xcb/*.h"]),
    visibility = ["//visibility:public"],
)

cc_import(
    name = "xtest",
    shared_library = "lib/libxcb-xtest.so",
    hdrs = ["include/xcb/xtest.h"],
    visibility = ["//visibility:public"],
)

cc_import(
    name = "keysyms",
    shared_library = "lib/libxcb-keysyms.so",
    hdrs = ["include/xcb/xcb_keysyms.h"],
    visibility = ["//visibility:public"],
)