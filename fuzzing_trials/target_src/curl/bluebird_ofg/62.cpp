#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include the header for memcpy

extern "C" {
    #include "curl/curl.h"
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
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
        curl_mimepart* ret_curl_mime_addpart_syjlo = curl_mime_addpart(NULL);
        if (ret_curl_mime_addpart_syjlo == NULL){
        	return 0;
        }

        CURLcode ret_curl_mime_filedata_zyvci = curl_mime_filedata(ret_curl_mime_addpart_syjlo, (const char *)curl);

        // End mutation: Producer.APPEND_MUTATOR

        curl_easy_cleanup(curl);
    }

    // Free the allocated memory
    free(ptr);

    return 0;
}