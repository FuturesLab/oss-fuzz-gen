#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Initialize CURL
    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        return 0;
    }

    // Set CURL options
    // Use the data as a URL if it's a valid string
    if (size > 0 && data[size - 1] == '\0') {
        curl_easy_setopt(curl, CURLOPT_URL, (const char *)data);
    } else {
        // If not a valid string, use a default URL
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    }

    // Perform the request
    CURLcode res = curl_easy_perform(curl);

    // Clean up
    curl_easy_cleanup(curl);

    return 0;
}