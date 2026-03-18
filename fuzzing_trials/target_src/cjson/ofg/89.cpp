#include <stdint.h>
#include <stdlib.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    // Check if the input data is not null and has a reasonable size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    cJSON *json_false = cJSON_CreateFalse();

    // Check if the creation was successful
    if (json_false != NULL) {
        // Perform operations on the created cJSON object if needed
        // For this test, we will just delete it to avoid memory leaks
        cJSON_Delete(json_false);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif