#include <cstddef>
#include <cstring>
#include <cstdint>  // Include for uint8_t
#include <curl/curl.h>

extern "C" {
    #include <curl/curl.h>
}

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to split into two strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two strings
    size_t mid = size / 2;
    const char *str1 = reinterpret_cast<const char *>(data);
    const char *str2 = reinterpret_cast<const char *>(data + mid);

    // Ensure both strings are null-terminated
    char *buffer1 = new char[mid + 1];
    char *buffer2 = new char[size - mid + 1];
    std::memcpy(buffer1, str1, mid);
    std::memcpy(buffer2, str2, size - mid);
    buffer1[mid] = '\0';
    buffer2[size - mid] = '\0';

    // Call the function-under-test
    int result = curl_strequal(buffer1, buffer2);

    // Clean up
    delete[] buffer1;
    delete[] buffer2;

    return 0;
}