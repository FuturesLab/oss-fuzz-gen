#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    CURL *curl;
    char *unescaped;
    int outlength;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Ensure the input data is null-terminated
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    unescaped = curl_easy_unescape(curl, input, (int)size, &outlength);

    // Clean up
    if (unescaped) {
        curl_free(unescaped);
    }
    free(input);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}