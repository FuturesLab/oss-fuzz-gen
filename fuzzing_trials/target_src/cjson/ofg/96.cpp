#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // Ensure the input is null-terminated
    char *input = (char *)malloc(size + 1);
    if (input == NULL) return 0;
    memcpy(input, data, size);
    input[size] = '\0';

    // Decide the value for require_null_terminated
    cJSON_bool require_null_terminated = (data[0] % 2 == 0) ? cJSON_True : cJSON_False;

    // Prepare a pointer for error handling
    const char *error_ptr = NULL;

    // Call the function-under-test
    cJSON *json = cJSON_ParseWithLengthOpts(input, size, &error_ptr, require_null_terminated);

    // Clean up
    if (json != NULL) {
        cJSON_Delete(json);
    }

    free(input);

    return 0;
}

#ifdef __cplusplus
}
#endif