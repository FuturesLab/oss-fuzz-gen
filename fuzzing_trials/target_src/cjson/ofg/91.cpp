#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Call the function-under-test
    cJSON *json = cJSON_ParseWithLength(input_data, size);

    // Clean up
    if (json != NULL) {
        cJSON_Delete(json);
    }
    free(input_data);

    return 0;
}

#ifdef __cplusplus
}
#endif