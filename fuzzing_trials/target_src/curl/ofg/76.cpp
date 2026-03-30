#include <cstddef>
#include <cstdint>
#include <cstring>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to create two non-empty strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for two strings
    size_t mid = size / 2;

    // Allocate memory for the two strings, ensuring null-termination
    char *str1 = new char[mid + 1];
    char *str2 = new char[size - mid + 1];

    // Copy data into the strings and null-terminate them
    memcpy(str1, data, mid);
    str1[mid] = '\0';

    memcpy(str2, data + mid, size - mid);
    str2[size - mid] = '\0';

    // Call the function-under-test
    int result = curl_strequal(str1, str2);

    // Clean up allocated memory
    delete[] str1;
    delete[] str2;

    return 0;
}