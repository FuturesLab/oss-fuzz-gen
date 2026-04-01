#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    const char *end_ptr = NULL;
    cJSON_bool require_null_termination = (data[0] % 2 == 0) ? 1 : 0;

    // Convert the input data to a null-terminated string
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Call the function-under-test
    cJSON *json = cJSON_ParseWithOpts(input_data, &end_ptr, require_null_termination);

    // Clean up
    if (json != NULL) {
        cJSON_Delete(json);
    }
    free(input_data);

    return 0;
}

#ifdef __cplusplus
}
#endif