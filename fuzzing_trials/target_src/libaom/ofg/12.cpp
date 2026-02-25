#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h> // Include the necessary header for aom_codec_av1_dx

extern "C" {
    aom_codec_err_t aom_codec_set_option(aom_codec_ctx_t *, const char *, const char *);
    const aom_codec_iface_t *aom_codec_av1_dx(); // Declare the function for the AV1 decoder
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    aom_codec_ctx_t codec_ctx;
    aom_codec_err_t result;

    // Initialize the codec context
    result = aom_codec_dec_init(&codec_ctx, aom_codec_av1_dx(), NULL, 0);
    if (result != AOM_CODEC_OK) {
        return 0; // Initialization failed, exit early
    }

    // Prepare options
    const char *option_name = "test_option";
    const char *option_value = (const char *)data;

    // Ensure the option value is null-terminated and within a reasonable size
    char option_value_buffer[256];
    size_t option_value_length = size < sizeof(option_value_buffer) - 1 ? size : sizeof(option_value_buffer) - 1;
    memcpy(option_value_buffer, data, option_value_length);
    option_value_buffer[option_value_length] = '\0'; // Null-terminate

    // Call the function under test
    result = aom_codec_set_option(&codec_ctx, option_name, option_value_buffer);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}