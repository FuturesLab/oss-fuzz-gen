#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    double number;
    memcpy(&number, data, sizeof(double));

    // Create a cJSON number object
    cJSON *json_number = cJSON_CreateNumber(number);

    if (json_number != NULL) {
        // Clean up the created cJSON object
        cJSON_Delete(json_number);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif