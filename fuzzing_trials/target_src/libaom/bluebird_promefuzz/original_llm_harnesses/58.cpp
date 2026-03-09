// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <aom/aom_integer.h>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom_encoder.h>
#include <aom/aom_external_partition.h>
#include <aom/aom.h>
#include <aom/aom_decoder.h>
#include <aom/aomcx.h>
#include <aom/aomdx.h>

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_err_t res = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);

    if (res != AOM_CODEC_OK) {
        return 0;
    }

    int param_value = 0;
    std::memcpy(&param_value, Data, sizeof(int));

    // Test AV1E_SET_FRAME_PERIODIC_BOOST
    aom_codec_control(&codec_ctx, AV1E_SET_FRAME_PERIODIC_BOOST, param_value);

    // Test AV1E_SET_DELTAQ_STRENGTH
    aom_codec_control(&codec_ctx, AV1E_SET_DELTAQ_STRENGTH, param_value);

    // Test AV1E_SET_BITRATE_ONE_PASS_CBR
    aom_codec_control(&codec_ctx, AV1E_SET_BITRATE_ONE_PASS_CBR, param_value);

    // Test AV1E_SET_AQ_MODE
    aom_codec_control(&codec_ctx, AV1E_SET_AQ_MODE, param_value);

    // Test AV1E_SET_FRAME_PARALLEL_DECODING
    aom_codec_control(&codec_ctx, AV1E_SET_FRAME_PARALLEL_DECODING, param_value);

    // Test AV1E_SET_ENABLE_RESTORATION
    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_RESTORATION, param_value);

    aom_codec_destroy(&codec_ctx);
    return 0;
}