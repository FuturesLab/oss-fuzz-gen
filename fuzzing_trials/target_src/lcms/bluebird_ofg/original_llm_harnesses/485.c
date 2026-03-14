#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <lcms2.h>   // Include for cmsUnregisterPlugins

int LLVMFuzzerTestOneInput_485(const uint8_t *data, size_t size) {
    // Since cmsUnregisterPlugins does not take any input parameters,
    // we can directly call it in the fuzzing harness.
    cmsUnregisterPlugins();

    return 0;
}