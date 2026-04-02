#include <cstddef>
#include <cstdint>
#include <cstring>
#include "curl/curl.h"

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Ensure the data is not empty and the size is within a reasonable range
    if (size == 0 || size > 1000) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *input = new char[size + 1];
    std::memcpy(input, data, size);
    input[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    char *escaped = curl_escape(input, static_cast<int>(size));

    // Clean up
    if (escaped != nullptr) {

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from curl_free to curl_strequal

        int ret_curl_strequal_qcswt = curl_strequal(NULL, (const char *)escaped);
        if (ret_curl_strequal_qcswt < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        curl_free(escaped);
    }
    delete[] input;

    return 0;
}