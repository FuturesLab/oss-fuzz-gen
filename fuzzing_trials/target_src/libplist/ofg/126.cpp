#include <stdint.h>
#include <stddef.h>

extern "C" {
    // Include the necessary header for libplist_version
    #include <plist/plist.h>
}

// Fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = libplist_version();

    // For demonstration purposes, we can print the version
    // In a real fuzzing scenario, this would not be necessary
    if (version != NULL) {
        // Do something with the version, if needed
        // For example, we could log it or check its format
    }

    return 0;
}