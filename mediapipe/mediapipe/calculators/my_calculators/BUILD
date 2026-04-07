licenses(["notice"])

package(default_visibility = [
    "//visibility:public",
])

cc_library (
    name = "my_simple_calculator",
    srcs = ["my_simple_calculator.cc"],
    deps = ["//mediapipe/framework:calculator_framework",
            "//mediapipe/framework/formats:landmark_cc_proto",
            "//mediapipe/framework:port",
            "//third_party/oscpack:oscpack",


            ],
    alwayslink = 1,
)

cc_library (
    name = "spout_sender_calculator",
    srcs = ["spout_sender_calculator.cc"],
    deps = ["//mediapipe/framework:calculator_framework",
            "//mediapipe/framework/formats:image_frame",
            ],
    alwayslink = 1,
)