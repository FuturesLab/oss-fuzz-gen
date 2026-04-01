#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>

extern "C" {
    // Include the necessary header for curl_strnequal
    #include <curl/curl.h>
}

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to split into two strings and a size_t
    if (size < 3) return 0;

    // Calculate the length for each string
    size_t str1_len = size / 2;
    size_t str2_len = size - str1_len;

    // Create buffers for the two strings
    char *str1 = new char[str1_len + 1];
    char *str2 = new char[str2_len + 1];

    // Copy data into the strings and null-terminate them
    memcpy(str1, data, str1_len);
    str1[str1_len] = '\0';

    memcpy(str2, data + str1_len, str2_len);
    str2[str2_len] = '\0';

    // Use a small size_t value for comparison
    size_t compare_len = size % (str1_len + 1);

    // Call the function-under-test
    int result = curl_strnequal(str1, str2, compare_len);

    // Clean up
    delete[] str1;
    delete[] str2;

    return 0;
}