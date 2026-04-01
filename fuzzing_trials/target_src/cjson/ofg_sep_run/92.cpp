#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the input is null-terminated to safely use it as a C string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    cJSON *json = cJSON_ParseWithLength(input, size);

    if (json != NULL) {
        cJSON_Delete(json);
    }

    free(input);
    return 0;
}

#ifdef __cplusplus
}
#endif