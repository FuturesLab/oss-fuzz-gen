#include <stdint.h>
#include <stddef.h>

// Declaration of the function-under-test
void hts_lib_shutdown();

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Since hts_lib_shutdown does not take any parameters, we can directly call it.
    hts_lib_shutdown();

    return 0;
}