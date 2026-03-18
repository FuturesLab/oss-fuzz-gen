#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *json_data = (char *)malloc(size + 1);
    if (json_data == NULL) {
        return 0;
    }
    memcpy(json_data, data, size);
    json_data[size] = '\0';

    // Parse the JSON data
    cJSON *json = cJSON_Parse(json_data);
    if (json != NULL) {
        // If parsing is successful, delete the cJSON object
        cJSON_Delete(json);
    }

    // Free the allocated memory for json_data
    free(json_data);

    return 0;
}

#ifdef __cplusplus
}
#endif