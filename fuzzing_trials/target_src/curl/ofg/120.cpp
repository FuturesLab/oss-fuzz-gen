#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    const char *cert_type = "PEM"; // Example certificate type
    const unsigned char *cert = data;
    size_t cert_len = size / 2; // Use half of the data for the certificate
    const unsigned char *key = data + cert_len;
    size_t key_len = size - cert_len; // Use the remaining data for the key

    if (size < 2) {
        return 0; // Not enough data to split into cert and key
    }

    curl = curl_easy_init();
    if (curl) {
        res = curl_easy_ssls_import(curl, cert_type, cert, cert_len, key, key_len);

        // Clean up
        curl_easy_cleanup(curl);
    }

    return 0;
}