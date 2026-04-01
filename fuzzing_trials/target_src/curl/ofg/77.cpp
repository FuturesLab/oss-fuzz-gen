#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Call the function-under-test
    CURL *curl = curl_easy_init();

    if (curl) {
        // Convert the input data to a string
        std::string url(reinterpret_cast<const char*>(data), size);

        // Set the URL option for the CURL handle
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Perform the request, ignoring the result for fuzzing purposes
        curl_easy_perform(curl);

        // Cleanup the CURL handle
        curl_easy_cleanup(curl);
    }

    return 0;
}