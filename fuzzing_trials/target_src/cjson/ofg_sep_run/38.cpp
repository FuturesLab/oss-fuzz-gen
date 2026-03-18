#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    if (size < 2) return 0;

    // Prepare a null-terminated key string
    char *key = (char *)malloc(size + 1);
    if (key == NULL) return 0;
    memcpy(key, data, size);
    key[size] = '\0';

    // Create a simple JSON object
    cJSON *json = cJSON_CreateObject();
    if (json == NULL) {
        free(key);
        return 0;
    }

    // Add a sample item to the JSON object
    cJSON_AddStringToObject(json, "sample_key", "sample_value");

    // Call the function-under-test
    cJSON *detached_item = cJSON_DetachItemFromObject(json, key);

    // Clean up
    if (detached_item != NULL) {
        cJSON_Delete(detached_item);
    }
    cJSON_Delete(json);
    free(key);

    return 0;
}

#ifdef __cplusplus
}
#endif