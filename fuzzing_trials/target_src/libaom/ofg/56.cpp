#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <aom/aom_codec.h>

extern "C" {

const char * aom_codec_error_detail(const aom_codec_ctx_t *);

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Ensure the size is within a reasonable limit for the codec context
    if (size < sizeof(aom_codec_ctx_t)) {
        return 0;
    }

    // Allocate and initialize the codec context
    aom_codec_ctx_t *codec_ctx = (aom_codec_ctx_t *)malloc(sizeof(aom_codec_ctx_t));
    if (codec_ctx == NULL) {
        return 0; // Memory allocation failed
    }

    // Fill the codec context with data from the input
    memcpy(codec_ctx, data, sizeof(aom_codec_ctx_t));

    // Call the function under test
    const char *error_detail = aom_codec_error_detail(codec_ctx);

    // Optionally, you could do something with error_detail here, like logging it

    // Clean up
    free(codec_ctx);
    
    return 0;
}

}