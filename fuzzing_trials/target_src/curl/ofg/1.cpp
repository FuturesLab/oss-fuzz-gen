#include <curl/curl.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Initialize CURL
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Ensure the input data is null-terminated for use as a string
    char *inputData = (char *)malloc(size + 1);
    if (!inputData) {
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Call the function-under-test
    char *escapedString = curl_easy_escape(curl, inputData, (int)size);

    // Cleanup
    if (escapedString) {
        curl_free(escapedString);
    }
    free(inputData);
    curl_easy_cleanup(curl);

    return 0;
}