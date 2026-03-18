#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    cJSON *json = NULL;
    cJSON *detached_item = NULL;
    char *key = NULL;

    // Ensure the input data is null-terminated for string operations
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    // Parse the input data as a JSON object
    json = cJSON_Parse((const char *)data);
    if (json == NULL) {
        return 0;
    }

    // Use a portion of the data as the key for detachment
    // Ensure the key is a valid null-terminated string
    size_t key_length = size / 2;
    key = (char *)malloc(key_length + 1);
    if (key == NULL) {
        cJSON_Delete(json);
        return 0;
    }
    memcpy(key, data, key_length);
    key[key_length] = '\0';

    // Detach the item from the JSON object
    detached_item = cJSON_DetachItemFromObject(json, key);

    // Free resources
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