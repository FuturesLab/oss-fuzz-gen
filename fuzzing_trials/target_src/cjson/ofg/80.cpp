#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    double num;
    memcpy(&num, data, sizeof(double));

    cJSON *json_number = cJSON_CreateNumber(num);
    if (json_number != NULL) {
        cJSON_Delete(json_number);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif