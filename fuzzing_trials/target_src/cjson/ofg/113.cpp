#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
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