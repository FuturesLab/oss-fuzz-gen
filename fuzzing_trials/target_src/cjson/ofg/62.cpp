#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    cJSON *json = cJSON_Parse((const char *)data);
    if (json == NULL) {
        return 0;
    }

    cJSON_bool is_number = cJSON_IsNumber(json);

    // Clean up
    cJSON_Delete(json);

    return 0;
}

#ifdef __cplusplus
}
#endif