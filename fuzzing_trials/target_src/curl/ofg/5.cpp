#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
    struct curl_header *curl_easy_nextheader(CURL *, unsigned int, int, struct curl_header *);
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    CURL *curl;
    struct curl_header *header = NULL;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Set some CURL options (this is optional and can be adjusted based on needs)
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");

    // Fuzzing parameters
    unsigned int header_type = size > 0 ? data[0] : 0; // Get header type from fuzz data
    int part = size > 1 ? data[1] : 0; // Get part from fuzz data

    // Call the function under test
    header = curl_easy_nextheader(curl, header_type, part, header);

    // Clean up
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}