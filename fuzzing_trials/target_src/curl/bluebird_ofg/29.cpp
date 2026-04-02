#include "curl/curl.h"
#include <stdint.h>
#include <stddef.h>

extern "C" {
    struct curl_header * curl_easy_nextheader(CURL *, unsigned int, int, struct curl_header *);
}

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    CURL *curl;
    struct curl_header *header = nullptr;
    unsigned int type = 0;
    int part = 0;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl == nullptr) {
        return 0;
    }

    // Set some options for CURL to make it ready for the test
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

    // Call the function-under-test
    header = curl_easy_nextheader(curl, type, part, header);

    // Cleanup
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}