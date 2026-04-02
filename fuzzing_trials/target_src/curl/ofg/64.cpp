#include <curl/curl.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl == NULL) {
        curl_global_cleanup();
        return 0;
    }

    // Ensure the size is sufficient for extracting option and value
    if (size < sizeof(CURLoption) + 1) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Extract CURLoption and value from the input data
    CURLoption option = static_cast<CURLoption>(data[0]);
    void *value = (void *)(data + sizeof(CURLoption));

    // Call the function-under-test
    res = curl_easy_setopt(curl, option, value);

    // Clean up
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}