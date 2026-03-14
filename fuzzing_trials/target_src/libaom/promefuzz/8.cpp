// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
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
#include <exception>
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aomdx.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_integer.h"
#include "aom_codec.h"
#include "aom_image.h"
#include "aom.h"
#include "aomcx.h"

static void cleanup(aom_codec_ctx_t *codec) {
    if (codec) {
        aom_codec_destroy(codec);
    }
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));
    
    // Initialize codec interface
    codec.iface = aom_codec_av1_cx();
    if (!codec.iface) return 0;

    // Initialize codec
    if (aom_codec_enc_init(&codec, codec.iface, nullptr, 0) != AOM_CODEC_OK) {
        cleanup(&codec);
        return 0;
    }

    // Use first byte to determine the control setting
    int control_value = Data[0] % 2;  // Just an example to derive a control value

    // Fuzz various control functions
    aom_codec_control(&codec, AV1E_SET_ERROR_RESILIENT_MODE, control_value);
    aom_codec_control(&codec, AV1E_SET_ENABLE_PALETTE, control_value);
    aom_codec_control(&codec, AV1E_SET_INTRA_DCT_ONLY, control_value);
    aom_codec_control(&codec, AV1E_SET_COLOR_PRIMARIES, control_value);
    aom_codec_control(&codec, AV1E_SET_ENABLE_SUPERRES, control_value);
    aom_codec_control(&codec, AV1E_SET_ENABLE_DIRECTIONAL_INTRA, control_value);

    cleanup(&codec);
    return 0;
}