licenses(["notice"])

package(default_visibility = ["//visibility:public"])

# Import the precompiled lib
cc_import(
    name = "spout_lib",
    interface_library = "lib/SpoutLibrary.lib",
    shared_library = "dll/SpoutLibrary.dll",  # ✅ CORRECT
)

# Spout cc_library
cc_library(
    name = "spout",
    hdrs = glob(["include/**/*.h"]),
    includes = ["include"],   # header root
    deps = [
        ":spout_lib",         # link the precompiled lib
    ],
    visibility = ["//visibility:public"],
)