#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURL *easy_handle;
    struct curl_waitfd waitfd;
    int numfds;
    CURLMcode res;

    // Initialize a CURLM handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Initialize a CURL easy handle
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Set a URL to fetch, using the input data as part of the URL
    // Ensure the data is null-terminated for safety
    char url[256] = "http://example.com/";
    strncat(url, reinterpret_cast<const char*>(data), size < 245 ? size : 245);

    curl_easy_setopt(easy_handle, CURLOPT_URL, url);
    curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, NULL); // Discard output

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Initialize the curl_waitfd structure
    waitfd.fd = 0; // File descriptor, 0 is standard input
    waitfd.events = CURL_WAIT_POLLIN; // Wait for incoming data
    waitfd.revents = 0; // Will be set by curl_multi_wait

    // Perform the multi interface operation
    res = curl_multi_wait(multi_handle, &waitfd, 1, 1000, &numfds);

    // Clean up
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}