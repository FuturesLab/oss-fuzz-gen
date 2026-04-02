#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "curl/curl.h"

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Initialize CURLU pointer
    CURLU *original_url = curl_url();
    if (!original_url) {
        return 0;
    }

    // Ensure data is null-terminated for use with curl_url_set
    char *url_data = (char *)malloc(size + 1);
    if (!url_data) {
        curl_url_cleanup(original_url);
        return 0;
    }
    memcpy(url_data, data, size);
    url_data[size] = '\0';

    // Set the URL in the original CURLU object

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of curl_url_set
    CURLUcode set_result = curl_url_set(original_url, CURLUPART_URL, url_data, CURLH_CONNECT);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    free(url_data);

    // Only proceed if the URL was set successfully
    if (set_result == CURLUE_OK) {
        // Call the function-under-test
        CURLU *duplicated_url = curl_url_dup(original_url);

        // Cleanup the duplicated URL
        if (duplicated_url) {
            curl_url_cleanup(duplicated_url);
        }
    }

    // Cleanup the original URL

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from curl_url_cleanup to curl_easy_unescape
    int pcnmrnbr = -1;

    char* ret_curl_easy_unescape_tdqxw = curl_easy_unescape((void *)original_url, (const char *)"r", CURLFINFOFLAG_KNOWN_FILENAME, &pcnmrnbr);
    if (ret_curl_easy_unescape_tdqxw == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    curl_url_cleanup(original_url);

    return 0;
}