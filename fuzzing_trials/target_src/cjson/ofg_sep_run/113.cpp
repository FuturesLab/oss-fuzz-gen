#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }

    // Calculate the number of integers we can extract from the data
    int num_ints = size / sizeof(int);
    if (num_ints <= 0) {
        return 0;
    }

    // Allocate memory for the integer array
    int *int_array = (int *)malloc(num_ints * sizeof(int));
    if (int_array == NULL) {
        return 0;
    }

    // Copy data into the integer array
    memcpy(int_array, data, num_ints * sizeof(int));

    // Call the function-under-test
    cJSON *json_array = cJSON_CreateIntArray(int_array, num_ints);

    // Clean up
    if (json_array != NULL) {
        cJSON_Delete(json_array);
    }
    free(int_array);

    return 0;
}

#ifdef __cplusplus
}
#endif