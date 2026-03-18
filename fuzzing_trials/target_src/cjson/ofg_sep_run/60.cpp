#include <stdint.h>
#include <stdlib.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Call the function-under-test
    cJSON *json_true = cJSON_CreateTrue();

    // Perform necessary operations to ensure code coverage
    if (json_true != NULL) {
        // Since cJSON_CreateTrue creates a JSON object representing true,
        // we can perform a simple check and then delete it.
        if (cJSON_IsTrue(json_true)) {
            // Optionally, convert to string and free the string
            char *json_string = cJSON_Print(json_true);
            if (json_string != NULL) {
                free(json_string);
            }
        }
        // Clean up the created JSON object
        cJSON_Delete(json_true);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif