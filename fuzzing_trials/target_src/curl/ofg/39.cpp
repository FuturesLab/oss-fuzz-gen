#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    CURLU *url;
    CURLUcode result;
    char *output = NULL;

    // Initialize a CURLU handle
    url = curl_url();
    if (!url) {
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *url_string = (char *)malloc(size + 1);
    if (!url_string) {
        curl_url_cleanup(url);
        return 0;
    }
    memcpy(url_string, data, size);
    url_string[size] = '\0';

    // Set the URL string to the CURLU handle
    curl_url_set(url, CURLUPART_URL, url_string, 0);

    // Fuzz different CURLUPart values
    CURLUPart parts[] = {
        CURLUPART_SCHEME,
        CURLUPART_HOST,
        CURLUPART_PORT,
        CURLUPART_PATH,
        CURLUPART_QUERY,
        CURLUPART_FRAGMENT,
        CURLUPART_USER,
        CURLUPART_PASSWORD,
        CURLUPART_OPTIONS,
        CURLUPART_ZONEID
    };

    size_t num_parts = sizeof(parts) / sizeof(parts[0]);
    for (size_t i = 0; i < num_parts; ++i) {
        // Call the function-under-test
        result = curl_url_get(url, parts[i], &output, 0);

        // Free the output if it was allocated
        if (output) {
            curl_free(output);
            output = NULL;
        }
    }

    // Clean up
    free(url_string);
    curl_url_cleanup(url);

    return 0;
}