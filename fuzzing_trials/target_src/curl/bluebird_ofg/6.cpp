#include <cstddef>
#include <cstdint>
#include "curl/curl.h"
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Initialize a CURLU object
    CURLU *url = curl_url();
    if (!url) {
        return 0;
    }

    // Convert the data to a null-terminated string
    char *url_part = new char[size + 1];
    memcpy(url_part, data, size);
    url_part[size] = '\0';

    // Try different CURLUParts
    CURLUPart parts[] = {
        CURLUPART_SCHEME,
        CURLUPART_USER,
        CURLUPART_PASSWORD,
        CURLUPART_OPTIONS,
        CURLUPART_HOST,
        CURLUPART_PORT,
        CURLUPART_PATH,
        CURLUPART_QUERY,
        CURLUPART_FRAGMENT,
        CURLUPART_ZONEID
    };

    // Iterate over all parts and fuzz the function
    for (CURLUPart part : parts) {
        // Use a fixed option for simplicity
        unsigned int flags = CURLU_NON_SUPPORT_SCHEME;

        // Call the function-under-test
        curl_url_set(url, part, url_part, flags);
    }

    // Clean up
    delete[] url_part;
    curl_url_cleanup(url);

    return 0;
}