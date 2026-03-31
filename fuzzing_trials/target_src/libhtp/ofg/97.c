#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "/src/libhtp/htp/htp.h"
#include "/src/libhtp/htp/bstr.h"

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Initialize the configuration
    htp_cfg_t *cfg = htp_config_create();
    if (cfg == NULL) {
        return 0;
    }

    // Initialize the decoder context using the correct enum type
    enum htp_decoder_ctx_t decoder_ctx = HTP_DECODER_URLENCODED;

    // Create a bstr object from the input data
    bstr *input_bstr = bstr_dup_mem((const char *)data, size);
    if (input_bstr == NULL) {
        htp_config_destroy(cfg);
        return 0;
    }

    // Initialize the other parameters
    uint64_t outlen = 0;
    int invalid_count = 0;

    // Call the function-under-test
    htp_status_t result = htp_urldecode_inplace_ex(cfg, decoder_ctx, input_bstr, &outlen, &invalid_count);

    // Clean up
    bstr_free(input_bstr);
    htp_config_destroy(cfg);

    return 0;
}