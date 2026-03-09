#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_143(const uint8_t* data, size_t size) {
    if (size < 2) return 0;

    // Split the input data into two parts for two JSON strings
    size_t half_size = size / 2;
    const char* json1_data = (const char*)data;
    const char* json2_data = (const char*)(data + half_size);

    // Ensure null-termination of the strings
    char* json1 = (char*)malloc(half_size + 1);
    char* json2 = (char*)malloc(size - half_size + 1);

    if (!json1 || !json2) {
        free(json1);
        free(json2);
        return 0;
    }

    memcpy(json1, json1_data, half_size);
    json1[half_size] = '\0';

    memcpy(json2, json2_data, size - half_size);
    json2[size - half_size] = '\0';

    // Parse the JSON strings
    cJSON* json1_parsed = cJSON_Parse(json1);
    cJSON* json2_parsed = cJSON_Parse(json2);

    if (json1_parsed && json2_parsed) {
        // Use the first byte of the input data to determine the cJSON_bool value
        cJSON_bool case_sensitive = (data[0] % 2 == 0) ? cJSON_True : cJSON_False;

        // Call the function under test
        cJSON_Compare((const cJSON*)json1_parsed, (const cJSON*)json2_parsed, case_sensitive);
    }

    // Cleanup
    cJSON_Delete(json1_parsed);
    cJSON_Delete(json2_parsed);
    free(json1);
    free(json2);

    return 0;
}

#ifdef __cplusplus
}
#endif