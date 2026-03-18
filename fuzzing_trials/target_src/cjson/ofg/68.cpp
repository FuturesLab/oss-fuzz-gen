#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = cJSON_Version();

    // Print the version to ensure the function is called
    printf("cJSON Version: %s\n", version);

    // The function cJSON_Version does not take any input or affect any state,
    // so there's nothing else to do with the fuzzer input here.

    return 0;
}

#ifdef __cplusplus
}
#endif