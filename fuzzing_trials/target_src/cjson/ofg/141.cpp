#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Ensure null-termination for the string
    char *input_string = (char *)malloc(size + 1);
    if (input_string == NULL) {
        return 0;
    }
    memcpy(input_string, data, size);
    input_string[size] = '\0';

    // Parse the input data as JSON
    cJSON *json = cJSON_Parse(input_string);
    if (json == NULL) {
        free(input_string);
        return 0;
    }

    // Use a part of the input data as the key for cJSON_HasObjectItem
    const char *key = input_string;
    if (strlen(key) == 0) {
        key = "default_key"; // Ensure key is not empty
    }

    // Call the function-under-test
    cJSON_bool result = cJSON_HasObjectItem(json, key);

    // Clean up
    cJSON_Delete(json);
    free(input_string);

    return 0;
}

#ifdef __cplusplus
}
#endif