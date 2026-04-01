#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a cJSON object
    cJSON *json = cJSON_CreateObject();
    if (json == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated
    char *string_data = (char *)malloc(size + 1);
    if (string_data == NULL) {
        cJSON_Delete(json);
        return 0;
    }
    memcpy(string_data, data, size);
    string_data[size] = '\0';

    // Call the function-under-test
    char *result = cJSON_SetValuestring(json, string_data);

    // Clean up
    free(string_data);
    cJSON_Delete(json);

    return 0;
}

#ifdef __cplusplus
}
#endif