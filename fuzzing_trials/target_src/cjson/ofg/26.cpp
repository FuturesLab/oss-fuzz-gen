#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    cJSON *json = cJSON_Parse((const char *)data);
    if (json == NULL) {
        return 0;
    }

    cJSON_bool is_raw = cJSON_IsRaw(json);

    // Use the result to avoid compiler warnings about unused variables
    (void)is_raw;

    cJSON_Delete(json);

    return 0;
}

#ifdef __cplusplus
}
#endif