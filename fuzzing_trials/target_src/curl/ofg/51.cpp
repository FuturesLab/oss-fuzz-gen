#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Initialize the CURL library
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Declare and initialize variables
    curl_sslbackend backend = CURLSSLBACKEND_NONE;
    const char *str = NULL;
    const curl_ssl_backend **backends = NULL;

    // Ensure size is large enough to extract meaningful data
    if (size > 0) {
        // Use the first byte to determine the backend
        backend = static_cast<curl_sslbackend>(data[0]);

        // Use the rest of the data as a string
        if (size > 1) {
            str = reinterpret_cast<const char*>(data + 1);
        }
    }

    // Call the function under test
    CURLsslset result = curl_global_sslset(backend, str, &backends);

    // Clean up
    curl_global_cleanup();

    return 0;
}