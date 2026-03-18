#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    if (size < 2) return 0;

    // Create a cJSON object
    cJSON *json_object = cJSON_CreateObject();
    if (json_object == NULL) return 0;

    // Use part of the data as the key
    size_t key_length = data[0] % size; // Ensure key length is within bounds
    char *key = (char *)malloc(key_length + 1);
    if (key == NULL) {
        cJSON_Delete(json_object);
        return 0;
    }
    memcpy(key, data + 1, key_length);
    key[key_length] = '\0';

    // Use the remaining data as the number
    double number = 0.0;
    if (size > key_length + 1) {
        memcpy(&number, data + key_length + 1, sizeof(double) <= size - key_length - 1 ? sizeof(double) : size - key_length - 1);
    }

    // Call the function-under-test
    cJSON *result = cJSON_AddNumberToObject(json_object, key, number);

    // Clean up
    free(key);
    cJSON_Delete(json_object);

    return 0;
}

#ifdef __cplusplus
}
#endif