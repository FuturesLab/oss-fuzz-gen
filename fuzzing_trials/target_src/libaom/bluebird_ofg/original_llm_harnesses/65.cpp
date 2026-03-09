#include <cstdint>
#include <cstdlib>

extern "C" {
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>

// Dummy callback functions for frame buffer operations
int get_frame_buffer_dummy(void *priv, size_t min_size, aom_codec_frame_buffer_t *fb) {
    // Allocate a buffer of the requested size
    fb->data = static_cast<uint8_t *>(malloc(min_size));
    fb->size = min_size;
    return (fb->data != NULL) ? 0 : -1; // Return 0 on success, -1 on failure
}

int release_frame_buffer_dummy(void *priv, aom_codec_frame_buffer_t *fb) {
    // Free the allocated buffer
    free(fb->data);
    fb->data = NULL;
    fb->size = 0;
    return 0; // Return 0 on success
}

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Initialize the codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx(); // Use AV1 decoder interface
    aom_codec_err_t res = aom_codec_dec_init(&codec_ctx, iface, NULL, 0);

    if (res != AOM_CODEC_OK) {
        return 0; // Exit if codec initialization fails
    }

    // Set the frame buffer functions with dummy callbacks
    aom_codec_set_frame_buffer_functions(&codec_ctx, get_frame_buffer_dummy, release_frame_buffer_dummy, NULL);

    // Decode the input data
    if (aom_codec_decode(&codec_ctx, data, size, NULL) != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0; // Exit if decoding fails
    }

    // Clean up the codec context
    aom_codec_destroy(&codec_ctx);

    return 0;
}

}