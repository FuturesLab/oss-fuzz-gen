#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    // Create a string reference using the input data
    cJSON *json_string_ref = cJSON_CreateStringReference((const char *)data);

    // Clean up the cJSON object if it was created
    if (json_string_ref != NULL) {
        cJSON_Delete(json_string_ref);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif