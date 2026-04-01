#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include the string.h library for memcpy
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Check if the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Parse the input data as a JSON string
    char *json_string = (char *)malloc(size + 1);
    if (json_string == NULL) {
        return 0;
    }
    memcpy(json_string, data, size);
    json_string[size] = '\0';

    // Call the function-under-test
    cJSON *json = cJSON_Parse(json_string);

    // Check if parsing was successful
    if (json != NULL) {
        // Perform operations on the parsed cJSON object if needed
        // For this fuzzing harness, we simply delete it to test memory handling
        cJSON_Delete(json);
    }

    free(json_string);
    return 0;
}

#ifdef __cplusplus
}
#endif