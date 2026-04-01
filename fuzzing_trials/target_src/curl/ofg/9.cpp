#include <curl/curl.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib> // For malloc and free

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    CURL *curl;
    char *unescaped = NULL;
    int outlength = 0;

    // Initialize a CURL handle
    curl = curl_easy_init();
    if(curl == NULL) {
        return 0; // If initialization fails, exit early
    }

    // Ensure the input data is treated as a null-terminated string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    unescaped = curl_easy_unescape(curl, input, (int)size, &outlength);

    // Clean up
    if (unescaped != NULL) {
        curl_free(unescaped);
    }
    free(input);
    curl_easy_cleanup(curl);

    return 0;
}