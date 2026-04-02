#include <cstddef>
#include <cstdint>
#include <curl/curl.h>
#include <cstring>
#include <cstdlib> // Include for malloc and free

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    CURL *curl;
    char *unescaped;
    int outlength;

    // Initialize CURL
    curl = curl_easy_init();
    if(curl == NULL) {
        return 0;
    }

    // Ensure that the input data is null-terminated before passing it to the function
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    unescaped = curl_easy_unescape(curl, input, (int)size, &outlength);

    // Free the allocated memory for unescaped string if it was allocated
    if(unescaped != NULL) {
        curl_free(unescaped);
    }

    // Free the input memory
    free(input);

    // Cleanup CURL
    curl_easy_cleanup(curl);

    return 0;
}