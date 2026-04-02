#include <cstddef>
#include <cstdint>
#include <curl/curl.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    CURL *curl;
    CURLcode res;
    size_t sent_bytes = 0;
    curl_off_t offset = 0;
    unsigned int flags = 0; // Example flag, adjust as needed

    // Convert the input data to a string to use as a URL
    std::string url(reinterpret_cast<const char*>(data), size);

    // Initialize a CURL session
    curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Set URL for the CURL session using the fuzz input data
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Set WebSocket options
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

    // Perform the WebSocket connection
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        return 0;
    }

    // Call the function-under-test
    res = curl_ws_send(curl, (const void *)data, size, &sent_bytes, offset, flags);

    // Clean up the CURL session
    curl_easy_cleanup(curl);

    return 0;
}