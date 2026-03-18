#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Check if the input data is not null and has a valid size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Parse the input data as a JSON string
    char *input_string = (char *)malloc(size + 1);
    if (input_string == NULL) {
        return 0; // Memory allocation failed
    }

    memcpy(input_string, data, size);
    input_string[size] = '\0'; // Null-terminate the string

    cJSON *json = cJSON_Parse(input_string);

    // Perform some basic operations on the parsed cJSON object
    if (json != NULL) {
        // Convert the cJSON object to a string
        char *json_string = cJSON_Print(json);
        if (json_string != NULL) {
            // Free the string after use
            free(json_string);
        }

        // Delete the cJSON object to free memory
        cJSON_Delete(json);
    }

    // Free the input string
    free(input_string);

    return 0;
}

#ifdef __cplusplus
}
#endif