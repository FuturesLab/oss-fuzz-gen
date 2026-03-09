#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts
    size_t json_data_size = size / 2;
    size_t key_size = size - json_data_size;

    char *json_data = (char *)malloc(json_data_size + 1);
    char *key = (char *)malloc(key_size + 1);

    if (json_data == NULL || key == NULL) {
        free(json_data);
        free(key);
        return 0;
    }

    memcpy(json_data, data, json_data_size);
    json_data[json_data_size] = '\0';

    memcpy(key, data + json_data_size, key_size);
    key[key_size] = '\0';

    cJSON *json = cJSON_Parse(json_data);
    if (json != NULL) {
        cJSON *detached_item = cJSON_DetachItemFromObjectCaseSensitive(json, key);
        if (detached_item != NULL) {
            cJSON_Delete(detached_item);
        }
        cJSON_Delete(json);
    }

    free(json_data);
    free(key);

    return 0;
}

#ifdef __cplusplus
}
#endif