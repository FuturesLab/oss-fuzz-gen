#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Assuming cmsBool is a typedef for a boolean type
typedef bool cmsBool;

// Fuzzing harness
int LLVMFuzzerTestOneInput_358(const uint8_t *data, size_t size) {
    // Ensure there is at least enough data to create a non-NULL pointer
    if (size < sizeof(void *)) {
        return 0;
    }

    // Use the data as a pointer to pass to cmsPlugin_358
    void *pluginData = (void *)data;

    // Call the function-under-test
    cmsBool result = cmsPlugin(pluginData);

    // Use the result in some way to avoid compiler optimizations
    if (result) {
        // Do something if true
    }

    return 0;
}