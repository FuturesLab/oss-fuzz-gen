#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cstdio>

extern "C" {
    #include <curl/curl.h>
}

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create two non-empty strings
    if (size < 2) return 0;

    // Split the input data into two parts for two strings
    size_t mid = size / 2;

    // Create two strings from the input data
    char *str1 = new char[mid + 1];
    char *str2 = new char[size - mid + 1];

    memcpy(str1, data, mid);
    memcpy(str2, data + mid, size - mid);

    // Null-terminate the strings
    str1[mid] = '\0';
    str2[size - mid] = '\0';

    // Call the function under test
    int result = curl_strequal(str1, str2);

    // Output the result for debugging purposes
    printf("Comparison result: %d\n", result);

    // Clean up
    delete[] str1;
    delete[] str2;

    return 0;
}