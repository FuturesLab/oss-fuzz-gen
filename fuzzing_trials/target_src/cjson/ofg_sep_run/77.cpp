#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    cJSON *json = cJSON_Parse((const char *)data);
    if (json == NULL) {
        return 0;
    }

    cJSON_bool result = cJSON_IsObject(json);

    // Use the result to prevent optimization out
    if (result) {
        cJSON *item = cJSON_GetObjectItem(json, "dummy_key");
        if (item != NULL) {
            cJSON_Delete(item);
        }
    }

    cJSON_Delete(json);

    return 0;
}

#ifdef __cplusplus
}
#endif