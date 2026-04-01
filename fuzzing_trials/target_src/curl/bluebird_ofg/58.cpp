#include "curl/curl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    CURL *curl;
    char *escaped_string;

    // Initialize a CURL handle
    curl = curl_easy_init();
    if(!curl) {
        return 0;
    }

    // Ensure the input data is null-terminated

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from curl_easy_init to curl_ws_send
    char yimtxmmt[1024] = "rwjai";
    CURLSHcode ret_curl_share_cleanup_cuqyx = curl_share_cleanup(yimtxmmt);
    size_t odswblbl = 0;

    CURLcode ret_curl_ws_send_ytafc = curl_ws_send(curl, (const void *)yimtxmmt, CURLPAUSE_SEND, &odswblbl, 0, CURL_POLL_IN);

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