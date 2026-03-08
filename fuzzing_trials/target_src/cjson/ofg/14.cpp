#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    if (size < sizeof(float) || size % sizeof(float) != 0) {
        return 0;
    }

    int num_floats = size / sizeof(float);
    float *float_array = (float *)malloc(size);
    if (float_array == NULL) {
        return 0;
    }

    memcpy(float_array, data, size);

    cJSON *json_array = cJSON_CreateFloatArray(float_array, num_floats);
    if (json_array != NULL) {
        cJSON_Delete(json_array);
    }

    free(float_array);
    return 0;
}

#ifdef __cplusplus
}
#endif