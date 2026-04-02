#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" {
    #include <curl/curl.h>
}

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for the two strings
    size_t half_size = size / 2;

    // Allocate memory for the two strings and ensure they are null-terminated
    char *str1 = (char *)malloc(half_size + 1);
    char *str2 = (char *)malloc(size - half_size + 1);

    if (!str1 || !str2) {
        free(str1);
        free(str2);
        return 0;
    }

    memcpy(str1, data, half_size);
    str1[half_size] = '\0';

    memcpy(str2, data + half_size, size - half_size);
    str2[size - half_size] = '\0';

    // Call the function-under-test
    int result = curl_strequal(str1, str2);

    // Clean up allocated memory
    free(str1);
    free(str2);

    return result;
}