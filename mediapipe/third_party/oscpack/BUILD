licenses(["notice"])

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "oscpack",
    srcs = glob([
        "osc/*.cpp",
        "ip/*.cpp",
        "ip/win32/*.cpp",
    ]),
    hdrs = glob([
        "osc/*.h",
        "ip/*.h",
        "ip/win32/*.h",
    ]),
    includes = ["."],  # relative to BUILD.bazel
    copts = [
        "/DOSC_HOST_LITTLE_ENDIAN",
        "/DOSC_PLATFORM_WINDOWS",
        "/DWIN32",
    ],
    linkopts = [
        "ws2_32.lib",
        "Winmm.lib",
    ],
)