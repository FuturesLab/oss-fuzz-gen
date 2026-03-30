#include "curl/curl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    CURL *curl;
    char *escaped_string;

    // Initialize a CURL handle
    curl = curl_easy_init();
    if(!curl) {
        return 0;
    }

    // Ensure the input data is null-terminated

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from curl_easy_init to curl_ws_send
    curl_easy_reset(curl);
    size_t odswblbl = -1;


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from curl_easy_reset to curl_formget
    struct curl_httppost huotnymm;
    memset(&huotnymm, 0, sizeof(huotnymm));

    int ret_curl_formget_gfkvd = curl_formget(&huotnymm, (void *)curl, NULL);
    if (ret_curl_formget_gfkvd < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    CURLcode ret_curl_ws_send_wjfzv = curl_ws_send(curl, (const void *)curl, CURLWS_PING, &odswblbl, 0, CURL_PUSH_ERROROUT);

    // End mutation: Producer.APPEND_MUTATOR

    char *input_string = (char *)malloc(size + 1);
    if (input_string == NULL) {
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(input_string, data, size);
    input_string[size] = '\0';

    // Call the function-under-test
    escaped_string = curl_easy_escape(curl, input_string, (int)size);

    // Cleanup
    if (escaped_string) {
        curl_free(escaped_string);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from curl_easy_escape to curl_mime_init

    curl_mime* ret_curl_mime_init_cmupj = curl_mime_init((void *)curl);
    if (ret_curl_mime_init_cmupj == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(input_string);
    curl_easy_cleanup(curl);

    return 0;
}