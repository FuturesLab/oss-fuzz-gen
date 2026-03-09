#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>  // Include for malloc and free
#include <string.h>  // Include for memcpy

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = cJSON_Version();
    
    // Print the version string to ensure the function is called
    printf("cJSON version: %s\n", version);

    // Create a cJSON object from the input data
    if (size > 0) {
        char *input = (char *)malloc(size + 1);
        if (input == NULL) {
            return 0;
        }
        memcpy(input, data, size);
        input[size] = '\0'; // Null-terminate the input data

        cJSON *json = cJSON_Parse(input);
        if (json != NULL) {
            // Successfully parsed JSON, perform operations on it
            cJSON_Delete(json);
        }

        free(input);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif