#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Initialize CURLM handle
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Initialize a CURL handle
    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Convert input data to a null-terminated string
    char *url = (char *)malloc(size + 1);
    if (!url) {
        curl_easy_cleanup(easy_handle);
        curl_multi_cleanup(multi_handle);
        return 0;
    }
    memcpy(url, data, size);
    url[size] = '\0';

    // Set the URL for the CURL handle
    curl_easy_setopt(easy_handle, CURLOPT_URL, url);

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Initialize fd_set structures
    fd_set read_fd_set;
    fd_set write_fd_set;
    fd_set exc_fd_set;
    
    // Initialize the fd_set structures
    FD_ZERO(&read_fd_set);
    FD_ZERO(&write_fd_set);
    FD_ZERO(&exc_fd_set);

    // Initialize the integer pointer
    int max_fd = -1;
    int still_running = 0;

    // Perform the function-under-test
    curl_multi_perform(multi_handle, &still_running);

    while (still_running) {
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        curl_multi_fdset(multi_handle, &read_fd_set, &write_fd_set, &exc_fd_set, &max_fd);
        if (max_fd == -1) {
            break;
        }

        select(max_fd + 1, &read_fd_set, &write_fd_set, &exc_fd_set, &timeout);

        curl_multi_perform(multi_handle, &still_running);
    }

    // Cleanup
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);
    free(url);

    return 0;
}