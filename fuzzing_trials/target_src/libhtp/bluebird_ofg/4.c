#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htp/htp.h" // Correct path to htp.h

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Initialize htp_cfg_t
    htp_cfg_t *cfg = htp_config_create();
    if (cfg == NULL) {
        return 0; // Failed to create configuration, exit early
    }

    // Initialize htp_decoder_ctx_t using enum
    enum htp_decoder_ctx_t decoder_ctx = HTP_DECODER_URLENCODED;

    // Initialize bstr
    bstr *url_string = bstr_dup_mem((const char *)data, size);
    if (url_string == NULL) {
        htp_config_destroy(cfg);
        return 0; // Failed to create bstr, exit early
    }

    // Initialize uint64_t
    uint64_t bytes_consumed = 0;

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bstr_dup_mem to bstr_index_of_c_nocasenorzero
    char* ret_bstr_util_strdup_to_c_muwry = bstr_util_strdup_to_c(url_string);
    if (ret_bstr_util_strdup_to_c_muwry == NULL){
    	return 0;
    }

    int ret_bstr_index_of_c_nocasenorzero_ustig = bstr_index_of_c_nocasenorzero(url_string, ret_bstr_util_strdup_to_c_muwry);
    if (ret_bstr_index_of_c_nocasenorzero_ustig < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    htp_status_t status = htp_urldecode_inplace(cfg, decoder_ctx, url_string, &bytes_consumed);

    // Cleanup
    bstr_free(url_string);
    htp_config_destroy(cfg);

    return 0;
}