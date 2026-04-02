#include <curl/curl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For memcpy

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    CURL *easy_handle;
    CURLcode result;
    struct curl_slist *header_list = NULL;

    // Initialize a CURL easy session
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        return 0;
    }

    // Ensure the data is null-terminated for string operations
    char *header_name = (char *)malloc(size + 1);
    if (!header_name) {
        curl_easy_cleanup(easy_handle);
        return 0;
    }
    memcpy(header_name, data, size);
    header_name[size] = '\0';

    // Add the header to the list
    header_list = curl_slist_append(header_list, header_name);

    // Set the headers for the CURL request
    result = curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, header_list);

    // Set a URL to ensure the request is performed
    result = curl_easy_setopt(easy_handle, CURLOPT_URL, "http://example.com");

    // Perform the request, ignore the result for fuzzing
    curl_easy_perform(easy_handle);

    // Clean up
    curl_slist_free_all(header_list);
    free(header_name);
    curl_easy_cleanup(easy_handle);

    return 0;
}