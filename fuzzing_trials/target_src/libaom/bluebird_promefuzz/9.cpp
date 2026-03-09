#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "/src/aom/aom/aom_codec.h"
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

static int dummy_get_frame_buffer(void *priv, size_t min_size, aom_codec_frame_buffer_t *fb) {
    (void)priv;
    (void)min_size;
    (void)fb;
    return 0;
}

static int dummy_release_frame_buffer(void *priv, aom_codec_frame_buffer_t *fb) {
    (void)priv;
    (void)fb;
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (dummy_file) {
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);
    }

    // aom_codec_av1_dx
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    if (!iface) return 0;

    // aom_codec_iface_name
    const char *iface_name = aom_codec_iface_name(iface);
    if (!iface_name) return 0;

    // aom_codec_get_caps
    aom_codec_caps_t caps = aom_codec_get_caps(iface);

    // aom_codec_dec_init_ver
    aom_codec_ctx_t ctx;
    aom_codec_err_t res = aom_codec_dec_init_ver(&ctx, iface, nullptr, 0, AOM_DECODER_ABI_VERSION);
    if (res != AOM_CODEC_OK) return 0;

    // aom_codec_set_frame_buffer_functions
    res = aom_codec_set_frame_buffer_functions(&ctx, dummy_get_frame_buffer, dummy_release_frame_buffer, nullptr);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&ctx);
        return 0;
    }

    // aom_codec_get_stream_info
    aom_codec_stream_info_t stream_info;
    res = aom_codec_get_stream_info(&ctx, &stream_info);

    // Cleanup
    aom_codec_destroy(&ctx);

    return 0;
}