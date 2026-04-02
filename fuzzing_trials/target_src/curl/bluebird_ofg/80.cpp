#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include the header for memcpy

extern "C" {
    #include "curl/curl.h"
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to prevent buffer overflow when used as a string
    char *ptr = (char *)malloc(size + 1); // Allocate extra byte for null terminator
    if (ptr == NULL) {
        return 0; // Allocation failed, exit early
    }

    // Copy the input data into the allocated memory and null-terminate it
    memcpy(ptr, data, size);
    ptr[size] = '\0'; // Null-terminate the string

    // Initialize a CURL handle
    CURL *curl = curl_easy_init();
    if(curl) {
        // Use the input data as a URL for testing
        curl_easy_setopt(curl, CURLOPT_URL, ptr);
        
        // Perform the request, ignoring the result
        curl_easy_perform(curl);

        // Cleanup

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from curl_easy_perform to curl_mime_filedata


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from curl_easy_perform to curl_mime_data_cb

        CURLcode ret_curl_mime_data_cb_kgioj = curl_mime_data_cb(NULL, 0, NULL, NULL, NULL, (void *)curl);

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function curl_mime_filedata with curl_mime_name
        CURLcode ret_curl_mime_filedata_eitfg = curl_mime_name(NULL, (const char *)curl);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // End mutation: Producer.APPEND_MUTATOR

        curl_easy_cleanup(curl);
    }

    // Free the allocated memory
    free(ptr);

    return 0;
}