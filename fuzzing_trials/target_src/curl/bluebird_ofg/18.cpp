#include "curl/curl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode result;
    struct curl_slist *headers = NULL;
    char *header_value = NULL;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        // Ensure data is not NULL and has a reasonable size
        if (size > 0 && data != NULL) {
            // Allocate memory for header value and copy data into it
            header_value = (char *)malloc(size + 1);
            if (header_value) {
                memcpy(header_value, data, size);
                header_value[size] = '\0'; // Null-terminate the string

                // Set the custom header
                headers = curl_slist_append(headers, header_value);
                if (headers) {
                    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

                    // Perform the request (this is just a placeholder URL)
                    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");

                    // Call the function under test
                    result = curl_easy_perform(curl);

                    // You might want to perform some checks or operations with 'result' here
                }

                // Free the allocated header value
                free(header_value);
            }
        }

        // Clean up the headers if they were set
        if (headers) {
            curl_slist_free_all(headers);
        }

        // Clean up CURL
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}