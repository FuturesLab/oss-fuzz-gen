#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create a root JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        return 0;
    }

    // Extract a boolean value from the first byte of data
    cJSON_bool bool_value = (data[0] % 2 == 0) ? cJSON_True : cJSON_False;

    // Ensure the string is null-terminated and has a minimum length
    size_t string_length = size - 1;
    char *key = (char *)malloc(string_length + 1);
    if (key == NULL) {
        cJSON_Delete(root);
        return 0;
    }
    memcpy(key, data + 1, string_length);
    key[string_length] = '\0';

    // Call the function-under-test
    cJSON *result = cJSON_AddBoolToObject(root, key, bool_value);

    // Clean up
    free(key);
    cJSON_Delete(root);

    return 0;
}

#ifdef __cplusplus
}
#endif