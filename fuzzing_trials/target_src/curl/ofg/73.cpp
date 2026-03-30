#include <cstddef>
#include <cstdint>
#include <cstring>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    // Ensure the input data is non-null and size is non-zero
    if (data == nullptr || size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputStr = new char[size + 1];
    memcpy(inputStr, data, size);
    inputStr[size] = '\0';

    // Call the function-under-test
    char *escapedStr = curl_escape(inputStr, static_cast<int>(size));

    // Clean up
    delete[] inputStr;
    if (escapedStr) {
        curl_free(escapedStr);
    }

    return 0;
}