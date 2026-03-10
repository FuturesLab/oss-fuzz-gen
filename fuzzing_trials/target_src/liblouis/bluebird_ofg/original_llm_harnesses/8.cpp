#include <stdint.h>
#include <stddef.h>

extern "C" {
    // Include the necessary header for the function-under-test
    #include "/src/liblouis/liblouis/liblouis.h"
}

// Fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = lou_version();

    // Use the returned version string in some way to ensure it's not optimized away
    if (version != nullptr) {
        // Perform a non-trivial operation to ensure the version string is used
        volatile size_t version_length = 0;
        while (version[version_length] != '\0') {
            version_length++;
        }
    }

    return 0;
}