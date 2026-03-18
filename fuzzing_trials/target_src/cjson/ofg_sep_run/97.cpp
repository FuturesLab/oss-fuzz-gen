#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // Create a cJSON array
    cJSON *array = cJSON_CreateArray();
    if (array == NULL) return 0;

    // Parse the input data as a JSON item
    cJSON *item = cJSON_ParseWithLength((const char *)data, size);
    if (item == NULL) {
        cJSON_Delete(array);
        return 0;
    }

    // Add the parsed item to the array
    cJSON_AddItemToArray(array, item);

    // Clean up
    cJSON_Delete(array);

    return 0;
}

#ifdef __cplusplus
}
#endif