#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    if (size < 3) return 0; // Ensure there is enough data to process

    // Parse the input data into cJSON objects
    cJSON *json1 = cJSON_Parse((const char *)data);
    if (json1 == NULL) return 0;

    // Create a new cJSON object to replace with
    cJSON *replace_with = cJSON_CreateString("replacement");

    // Create a target cJSON object
    cJSON *target = cJSON_CreateString("target");

    // Call the function-under-test
    cJSON_ReplaceItemViaPointer(json1, target, replace_with);

    // Clean up
    cJSON_Delete(json1);
    cJSON_Delete(target);
    cJSON_Delete(replace_with);

    return 0;
}

#ifdef __cplusplus
}
#endif