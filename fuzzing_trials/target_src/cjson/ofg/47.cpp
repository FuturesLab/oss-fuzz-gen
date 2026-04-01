#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    cJSON *json = cJSON_ParseWithLength((const char *)data, size);
    if (json == NULL) return 0;

    int prebuffer_size = 1024; // Set a default prebuffer size
    cJSON_bool format = (data[0] % 2 == 0) ? cJSON_True : cJSON_False;

    char *printed_json = cJSON_PrintBuffered(json, prebuffer_size, format);
    if (printed_json != NULL) {
        free(printed_json);
    }

    cJSON_Delete(json);
    return 0;
}

#ifdef __cplusplus
}
#endif