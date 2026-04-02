#include <curl/curl.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated
    char *input = new char[size + 1];
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    CURLcode result = curl_global_trace(input);

    // Clean up
    delete[] input;

    return 0;
}