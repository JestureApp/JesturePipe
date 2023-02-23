"""
Second part of setup. Necessary to split these into separate files because of
tensorflow.
"""

load("@org_tensorflow//tensorflow:workspace2.bzl", "tf_workspace2")

def jesturepipe_setup1():
    tf_workspace2()
