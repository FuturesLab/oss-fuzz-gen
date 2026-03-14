#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read a cmsFloat64Number
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Interpret the first bytes of data as a cmsFloat64Number
    cmsFloat64Number adaptationState;
    memcpy(&adaptationState, data, sizeof(cmsFloat64Number));

    // Call the function-under-test
    cmsFloat64Number result = cmsSetAdaptationState(adaptationState);

    // Use the result in some way to avoid any compiler optimizations
    volatile cmsFloat64Number use_result = result;
    (void)use_result;

    return 0;
}