#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    if (size < 2) return 0;

    // Split the input data into two parts for two cJSON objects
    size_t half_size = size / 2;
    const uint8_t *data1 = data;
    size_t size1 = half_size;
    const uint8_t *data2 = data + half_size;
    size_t size2 = size - half_size;

    // Ensure the last byte of each part is null-terminated
    char *json_string1 = (char *)malloc(size1 + 1);
    char *json_string2 = (char *)malloc(size2 + 1);

    if (!json_string1 || !json_string2) {
        free(json_string1);
        free(json_string2);
        return 0;
    }

    memcpy(json_string1, data1, size1);
    json_string1[size1] = '\0';

    memcpy(json_string2, data2, size2);
    json_string2[size2] = '\0';

    // Parse the JSON strings into cJSON objects
    cJSON *json1 = cJSON_Parse(json_string1);
    cJSON *json2 = cJSON_Parse(json_string2);

    free(json_string1);
    free(json_string2);

    if (!json1 || !json2) {
        cJSON_Delete(json1);
        cJSON_Delete(json2);
        return 0;
    }

    // Use the first byte of the input data to determine the cJSON_bool value
    cJSON_bool case_sensitive = data[0] % 2 == 0 ? cJSON_True : cJSON_False;

    // Call the function-under-test
    cJSON_Compare(json1, json2, case_sensitive);

    // Clean up
    cJSON_Delete(json1);
    cJSON_Delete(json2);

    return 0;
}

#ifdef __cplusplus
}
#endif