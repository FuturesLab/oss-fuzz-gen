#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    if (size < 2) return 0; // Ensure there's at least one byte for a string and one for a number

    // Create a root cJSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) return 0;

    // Use the data to create a string key
    size_t key_length = data[0] % (size - 1) + 1; // Ensure key_length is within bounds
    char *key = (char *)malloc(key_length + 1);
    if (key == NULL) {
        cJSON_Delete(root);
        return 0;
    }
    memcpy(key, data + 1, key_length);
    key[key_length] = '\0'; // Null-terminate the string

    // Use the remaining data to create a double value
    double number = 0.0;
    if (size > key_length + 1) {
        memcpy(&number, data + key_length + 1, sizeof(double) <= size - key_length - 1 ? sizeof(double) : size - key_length - 1);
    }

    // Call the function-under-test
    cJSON *result = cJSON_AddNumberToObject(root, key, number);

    // Clean up
    free(key);
    cJSON_Delete(root);

    return 0;
}

#ifdef __cplusplus
}
#endif