#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0;
    }

    // Split the input data into three parts
    size_t part1_size = data[0] % size;
    size_t part2_size = (data[1] % (size - part1_size));
    size_t part3_size = size - part1_size - part2_size - 2;

    const uint8_t *part1 = data + 1;
    const uint8_t *part2 = part1 + part1_size;
    const uint8_t *part3 = part2 + part2_size;

    // Create cJSON objects from the parts
    cJSON *object = cJSON_ParseWithLength((const char *)part1, part1_size);
    cJSON *new_item = cJSON_ParseWithLength((const char *)part3, part3_size);

    if (object == NULL || new_item == NULL) {
        cJSON_Delete(object);
        cJSON_Delete(new_item);
        return 0;
    }

    // Ensure part2 is null-terminated for use as a key
    char *key = (char *)malloc(part2_size + 1);
    if (key == NULL) {
        cJSON_Delete(object);
        cJSON_Delete(new_item);
        return 0;
    }
    memcpy(key, part2, part2_size);
    key[part2_size] = '\0';

    // Call the function-under-test
    cJSON_bool result = cJSON_ReplaceItemInObjectCaseSensitive(object, key, new_item);

    // Clean up
    free(key);
    cJSON_Delete(object);
    // Note: new_item is already deleted by cJSON_ReplaceItemInObjectCaseSensitive if successful

    return 0;
}

#ifdef __cplusplus
}
#endif