#include <stdint.h>
#include <stddef.h>
#include <string>

extern "C" {
#include <curl/curl.h>
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Initialize libcurl globally
    CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
    if (res != CURLE_OK) {
        return 0; // Initialization failed, exit early
    }

    // Initialize a CURL handle
    CURL *curl = curl_easy_init();
    if (curl) {
        // Convert the input data to a string
        std::string url(data, data + size);

        // Set the URL option
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Perform the request
        curl_easy_perform(curl);

        // Cleanup the CURL handle
        curl_easy_cleanup(curl);
    }

    // Cleanup libcurl globally
    curl_global_cleanup();

    return 0;
}