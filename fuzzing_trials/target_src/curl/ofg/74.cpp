#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib> // Include for malloc and free
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *inputStr = static_cast<char *>(malloc(size + 1));
    if (inputStr == NULL) {
        return 0;
    }

    // Copy the data into the string and null-terminate it
    memcpy(inputStr, data, size);
    inputStr[size] = '\0';

    // Call the function-under-test
    int length = static_cast<int>(size);
    char *escapedStr = curl_escape(inputStr, length);

    // Clean up
    free(inputStr);
    if (escapedStr != NULL) {
        curl_free(escapedStr);
    }

    return 0;
}