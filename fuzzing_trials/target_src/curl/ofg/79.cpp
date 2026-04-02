#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/select.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURL *easy_handle;
    fd_set read_fd_set;
    fd_set write_fd_set;
    fd_set exc_fd_set;
    int max_fd = -1;
    CURLMcode result;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Initialize a multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        curl_global_cleanup();
        return 0;
    }

    // Initialize an easy handle
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        curl_global_cleanup();
        return 0;
    }

    // Set a URL for the easy handle
    char url[256];
    snprintf(url, sizeof(url), "http://example.com/%.*s", (int)size, data);
    curl_easy_setopt(easy_handle, CURLOPT_URL, url);

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Initialize file descriptor sets
    FD_ZERO(&read_fd_set);
    FD_ZERO(&write_fd_set);
    FD_ZERO(&exc_fd_set);

    // Call the function-under-test
    result = curl_multi_fdset(multi_handle, &read_fd_set, &write_fd_set, &exc_fd_set, &max_fd);

    // Perform the multi handle operation
    int still_running;
    curl_multi_perform(multi_handle, &still_running);

    // Cleanup
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}