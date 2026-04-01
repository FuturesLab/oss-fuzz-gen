#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    if (size < 2) return 0;

    // Determine the number of strings to create
    int num_strings = data[0] % 10 + 1; // Ensure at least 1 string

    // Allocate memory for the array of string pointers
    const char **string_array = (const char **)malloc(num_strings * sizeof(char *));
    if (!string_array) return 0;

    size_t offset = 1;
    for (int i = 0; i < num_strings; i++) {
        if (offset >= size) {
            string_array[i] = strdup("default"); // Fallback to a default string
        } else {
            size_t str_len = data[offset] % (size - offset) + 1; // Ensure at least 1 character
            string_array[i] = (char *)malloc(str_len + 1);
            if (string_array[i]) {
                memcpy((char *)string_array[i], data + offset, str_len);
                ((char *)string_array[i])[str_len] = '\0';
            } else {
                string_array[i] = strdup("default"); // Fallback to a default string
            }
            offset += str_len;
        }
    }

    // Call the function-under-test
    cJSON *json_array = cJSON_CreateStringArray(string_array, num_strings);

    // Clean up
    for (int i = 0; i < num_strings; i++) {
        free((void *)string_array[i]);
    }
    free(string_array);

    // Delete the created cJSON object
    if (json_array) {
        cJSON_Delete(json_array);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif