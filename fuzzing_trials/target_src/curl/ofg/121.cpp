#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    const char *ssltype = "PEM"; // Assuming a valid SSL type for testing

    // Initialize a CURL session
    curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Split the input data into two parts for the two unsigned char* parameters
    size_t half_size = size / 2;
    const unsigned char *ssl_cert = data;
    size_t ssl_cert_size = half_size;
    const unsigned char *ssl_key = data + half_size;
    size_t ssl_key_size = size - half_size;

    // Call the function-under-test
    res = curl_easy_ssls_import(curl, ssltype, ssl_cert, ssl_cert_size, ssl_key, ssl_key_size);

    // Cleanup the CURL session
    curl_easy_cleanup(curl);

    return 0;
}