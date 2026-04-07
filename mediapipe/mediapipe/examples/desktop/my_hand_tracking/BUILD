

licenses(["notice"])

package(default_visibility = ["//mediapipe/examples:__subpackages__"])


cc_binary(
    name = "my_hand_tracking",
    data = [
        "//mediapipe/modules/hand_landmark:hand_landmark_full.tflite",
        "//mediapipe/modules/palm_detection:palm_detection_full.tflite",
    ],
    deps = [
        "//mediapipe/examples/desktop:MY_demo_run_graph",
        "//mediapipe/graphs/hand_tracking:desktop_tflite_calculators",
        "//mediapipe/calculators/my_calculators:my_simple_calculator",

    ],
)
