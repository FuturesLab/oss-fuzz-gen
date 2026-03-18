#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create a root JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        return 0;
    }

    // Use the first byte to determine the boolean value
    cJSON_bool bool_value = (data[0] % 2 == 0) ? cJSON_True : cJSON_False;

    // Use the rest of the data as a key, ensuring null termination
    char *key = (char *)malloc(size);
    if (key == NULL) {
        cJSON_Delete(root);
        return 0;
    }
    memcpy(key, data + 1, size - 1);
    key[size - 1] = '\0';

    // Call the function under test
    cJSON *result = cJSON_AddBoolToObject(root, key, bool_value);

    // Clean up
    free(key);
    cJSON_Delete(root);

    return 0;
}

#ifdef __cplusplus
}
#endif