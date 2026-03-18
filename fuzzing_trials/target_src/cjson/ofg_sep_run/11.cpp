#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the input data is null-terminated to be used as a string
    char *json_string = (char *)malloc(size + 1);
    if (json_string == NULL) {
        return 0;
    }
    memcpy(json_string, data, size);
    json_string[size] = '\0';

    // Parse the JSON string
    cJSON *json = cJSON_Parse(json_string);

    // If parsing was successful, delete the cJSON object
    if (json != NULL) {
        cJSON_Delete(json);
    }

    // Free the allocated memory for the JSON string
    free(json_string);

    return 0;
}

#ifdef __cplusplus
}
#endif