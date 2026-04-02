#include <cstddef>
#include <cstdint>
#include <cstring>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure there is enough data to split into two strings and a size_t
    if (size < 3) {
        return 0;
    }

    // Split the data into two parts for the strings
    size_t split_point = size / 2;

    // Create null-terminated strings from the data
    char *str1 = new char[split_point + 1];
    char *str2 = new char[size - split_point + 1];

    memcpy(str1, data, split_point);
    str1[split_point] = '\0';

    memcpy(str2, data + split_point, size - split_point);
    str2[size - split_point] = '\0';

    // Use a size_t value for comparison length, ensure it's not larger than the strings
    size_t compare_length = split_point < (size - split_point) ? split_point : (size - split_point);

    // Call the function-under-test
    int result = curl_strnequal(str1, str2, compare_length);

    // Clean up
    delete[] str1;
    delete[] str2;

    return 0;
}