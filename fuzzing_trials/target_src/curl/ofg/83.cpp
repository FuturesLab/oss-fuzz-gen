#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    // Ensure size is non-zero and data is not NULL
    if (size == 0 || data == NULL) {
        return 0;
    }

    // Allocate memory for the input string and ensure it's null-terminated
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    curl_global_trace(input_str);

    // Clean up
    free(input_str);

    return 0;
}