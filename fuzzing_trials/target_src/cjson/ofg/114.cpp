#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }

    int array_size = size / sizeof(int);
    int *int_array = (int *)malloc(array_size * sizeof(int));
    if (int_array == NULL) {
        return 0;
    }

    memcpy(int_array, data, array_size * sizeof(int));

    cJSON *json_array = cJSON_CreateIntArray(int_array, array_size);

    if (json_array != NULL) {
        cJSON_Delete(json_array);
    }

    free(int_array);

    return 0;
}

#ifdef __cplusplus
}
#endif