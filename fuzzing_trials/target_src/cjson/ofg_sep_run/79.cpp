#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include this library for memcpy
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    double number;
    // Copy the input data into the double variable
    memcpy(&number, data, sizeof(double));

    // Call the function-under-test
    cJSON *json_number = cJSON_CreateNumber(number);

    // Clean up
    if (json_number != NULL) {
        cJSON_Delete(json_number);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif