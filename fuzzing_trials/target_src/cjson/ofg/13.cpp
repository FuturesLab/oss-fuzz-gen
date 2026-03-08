#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    if (size < sizeof(float)) {
        return 0;
    }

    int array_size = size / sizeof(float);
    float *float_array = (float *)malloc(array_size * sizeof(float));

    if (float_array == NULL) {
        return 0;
    }

    memcpy(float_array, data, array_size * sizeof(float));

    cJSON *json_array = cJSON_CreateFloatArray(float_array, array_size);

    if (json_array != NULL) {
        cJSON_Delete(json_array);
    }

    free(float_array);

    return 0;
}

#ifdef __cplusplus
}
#endif