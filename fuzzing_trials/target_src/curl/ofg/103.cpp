#include <curl/curl.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

// Ensure C linkage for the libcurl functions
extern "C" {
    #include <curl/curl.h>
}

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    CURL *easy_handle = curl_easy_init();

    if (easy_handle == nullptr) {
        return 0;
    }

    if (size > 0) {
        // Use the fuzzing data as a URL
        char *url = new char[size + 1];
        memcpy(url, data, size);
        url[size] = '\0';

        // Set the URL using libcurl's API
        curl_easy_setopt(easy_handle, CURLOPT_URL, url);

        // Optionally, set the header using libcurl's API
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/octet-stream");
        curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, headers);

        // Perform the request
        curl_easy_perform(easy_handle);

        // Clean up
        delete[] url;
        if (headers) {
            curl_slist_free_all(headers);
        }
    }

    curl_easy_cleanup(easy_handle);
    return 0;
}