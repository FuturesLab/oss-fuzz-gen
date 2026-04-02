#include "curl/curl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURL *easy_handle;
    struct curl_waitfd waitfd;
    int numfds;
    int still_running; // to store number of handles still running
    CURLMsg *msg;
    int msgs_left;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        curl_global_cleanup();
        return 0;
    }

    // Create an easy handle
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        curl_global_cleanup();
        return 0;
    }

    // Set options for the easy handle
    // Use the fuzzing input as the URL
    char url[256];
    snprintf(url, sizeof(url), "http://example.com/%.*s", (int)size, data);
    curl_easy_setopt(easy_handle, CURLOPT_URL, url);

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Perform the multi handle operations
    curl_multi_perform(multi_handle, &still_running);

    // Initialize the curl_waitfd structure
    waitfd.fd = 0; // File descriptor (0 is stdin, just for example)
    waitfd.events = CURL_WAIT_POLLIN; // Set to wait for read events
    waitfd.revents = 0; // Reset returned events

    // Wait for activity on the multi handle
    curl_multi_wait(multi_handle, &waitfd, 1, 1000, &numfds);

    // Check for completed transfers
    while ((msg = curl_multi_info_read(multi_handle, &msgs_left))) {
        if (msg->msg == CURLMSG_DONE) {
            // Handle completed transfer
        }
    }

    // Clean up
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}