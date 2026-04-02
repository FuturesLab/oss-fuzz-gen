#include <cstddef>
#include <cstdint>
#include <curl/curl.h>
#include <unistd.h>
#include <sys/socket.h>  // Include necessary for socketpair

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURL *easy_handle;
    int running_handles;

    // Initialize CURL multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Initialize CURL easy handle
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Set the URL to a test server or a dummy URL
    curl_easy_setopt(easy_handle, CURLOPT_URL, "http://example.com");

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Perform the multi handle operation
    CURLMcode result;
    do {
        result = curl_multi_perform(multi_handle, &running_handles);
    } while (result == CURLM_CALL_MULTI_PERFORM);

    // Clean up
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}