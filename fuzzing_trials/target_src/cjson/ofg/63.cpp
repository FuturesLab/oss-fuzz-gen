#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Parse the input data to create a cJSON object
    cJSON *json = cJSON_Parse((const char *)data);
    if (json == NULL) {
        return 0;
    }

    // Allocate memory for the output buffer
    int buffer_size = (int)size;
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        cJSON_Delete(json);
        return 0;
    }

    // Determine if the output should be formatted
    cJSON_bool formatted = (data[0] % 2 == 0) ? cJSON_True : cJSON_False;

    // Call the function under test
    cJSON_bool result = cJSON_PrintPreallocated(json, buffer, buffer_size, formatted);

    // Clean up
    free(buffer);
    cJSON_Delete(json);

    return 0;
}

#ifdef __cplusplus
}
#endif