// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_control_typechecked_AOME_SET_ARNR_STRENGTH at aomcx.h:1931:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_ENABLEAUTOALTREF at aomcx.h:1913:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_ARNR_MAXFRAMES at aomcx.h:1928:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_SHARPNESS at aomcx.h:1916:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_CPUUSED at aomcx.h:1910:1 in aomcx.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "aomdx.h"
#include "aom_external_partition.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom.h"
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aom_frame_buffer.h"
#include "aom_integer.h"
#include "aomcx.h"

static aom_codec_ctx_t codec_ctx;

static void initialize_codec() {
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_err_t res = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Failed to initialize codec: " << codec_ctx.err << std::endl;
    }
}

static void cleanup_codec() {
    aom_codec_destroy(&codec_ctx);
}

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0; // Ensure we have enough data

    initialize_codec();

    // Example of using the fuzz data
    unsigned int strength = Data[0] % 64; // ARNR strength (0-63)
    unsigned int enable_auto_alt_ref = Data[1] % 2; // Enable/disable auto alt ref
    unsigned int max_frames = Data[2] % 16; // Max ARNR frames (0-15)
    unsigned int sharpness = Data[3] % 7; // Sharpness level (0-6)
    int cpu_used = Data[4] % 8; // CPU usage (0-7)

    // Fuzzing different API functions
    aom_codec_control_typechecked_AOME_SET_ARNR_STRENGTH(&codec_ctx, AOME_SET_ARNR_STRENGTH, strength);
    aom_codec_control_typechecked_AOME_SET_ENABLEAUTOALTREF(&codec_ctx, AOME_SET_ENABLEAUTOALTREF, enable_auto_alt_ref);
    aom_codec_control_typechecked_AOME_SET_ARNR_MAXFRAMES(&codec_ctx, AOME_SET_ARNR_MAXFRAMES, max_frames);
    aom_codec_control_typechecked_AOME_SET_SHARPNESS(&codec_ctx, AOME_SET_SHARPNESS, sharpness);
    aom_codec_control_typechecked_AOME_SET_CPUUSED(&codec_ctx, AOME_SET_CPUUSED, cpu_used);

    // Cleanup
    cleanup_codec();

    return 0;
}