#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    if (size < 2) return 0;

    // Create a root JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) return 0;

    // Split the input data into two parts for key and value
    size_t key_len = data[0] % size; // Ensure key_len is within bounds
    size_t value_len = size - key_len - 1; // Ensure there's space for the value

    if (key_len == 0 || value_len == 0) {
        cJSON_Delete(root);
        return 0;
    }

    // Allocate memory for key and value
    char *key = (char *)malloc(key_len + 1);
    char *value = (char *)malloc(value_len + 1);

    if (key == NULL || value == NULL) {
        free(key);
        free(value);
        cJSON_Delete(root);
        return 0;
    }

    // Copy data into key and value
    memcpy(key, data + 1, key_len);
    key[key_len] = '\0'; // Null-terminate the key

    memcpy(value, data + 1 + key_len, value_len);
    value[value_len] = '\0'; // Null-terminate the value

    // Call the function-under-test
    cJSON *result = cJSON_AddStringToObject(root, key, value);

    // Clean up
    free(key);
    free(value);
    cJSON_Delete(root);

    return 0;
}

#ifdef __cplusplus
}
#endif