#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    const char *end_ptr = NULL;
    cJSON_bool require_null_terminated = cJSON_True;

    // Parse the JSON data using cJSON_ParseWithOpts
    cJSON *json = cJSON_ParseWithOpts((const char *)data, &end_ptr, require_null_terminated);

    // Clean up the cJSON object if it was successfully created
    if (json != NULL) {
        cJSON_Delete(json);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif