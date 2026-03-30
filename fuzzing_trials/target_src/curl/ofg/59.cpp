#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {

void* custom_malloc_59(size_t size) {
    return malloc(size);
}

void custom_free_59(void* ptr) {
    free(ptr);
}

void* custom_realloc_59(void* ptr, size_t size) {
    return realloc(ptr, size);
}

char* custom_strdup_59(const char* str) {
    return strdup(str);
}

void* custom_calloc_59(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}

}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Initialize with a non-zero value for the 'flags' parameter
    long flags = CURL_GLOBAL_ALL;

    // Call the function-under-test
    CURLcode result = curl_global_init_mem(
        flags,
        custom_malloc_59,
        custom_free_59,
        custom_realloc_59,
        custom_strdup_59,
        custom_calloc_59
    );

    // Check the result
    if (result == CURLE_OK) {
        CURL *curl = curl_easy_init();
        if(curl) {
            // Use the input data as a URL
            // Ensure the data is null-terminated
            char *url = (char *)malloc(size + 1);
            if (url) {
                memcpy(url, data, size);
                url[size] = '\0';

                // Set the URL
                curl_easy_setopt(curl, CURLOPT_URL, url);

                // Perform the request
                curl_easy_perform(curl);

                // Clean up
                free(url);
            }
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
    }

    return 0;
}