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

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 7) return 0; // Ensure there's enough data

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx(); // Get AV1 codec interface
    aom_codec_err_t res = aom_codec_enc_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Fuzzing aom_codec_control_typechecked_AV1E_SET_RENDER_SIZE
    int width = Data[0] % 4096; // Random width up to 4096
    int height = Data[1] % 4096; // Random height up to 4096
    res = aom_codec_control(&codec, AV1E_SET_RENDER_SIZE, width, height);
    
    // Fuzzing aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION
    int chroma_sample_position = Data[2] % 3; // Random value for chroma sample position
    res = aom_codec_control(&codec, AV1E_SET_CHROMA_SAMPLE_POSITION, chroma_sample_position);
    
    // Fuzzing aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE
    int enable_palette = Data[3] % 2; // Random boolean for enabling palette
    res = aom_codec_control(&codec, AV1E_SET_ENABLE_PALETTE, enable_palette);
    
    // Fuzzing aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS
    int matrix_coefficients = Data[4] % 6; // Random value for matrix coefficients
    res = aom_codec_control(&codec, AV1E_SET_MATRIX_COEFFICIENTS, matrix_coefficients);
    
    // Fuzzing aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS
    int quantizer = Data[5] % 64; // Random quantizer value
    res = aom_codec_control(&codec, AV1E_SET_QUANTIZER_ONE_PASS, quantizer);
    
    // Fuzzing aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES
    int color_primaries = Data[6] % 10; // Random value for color primaries
    res = aom_codec_control(&codec, AV1E_SET_COLOR_PRIMARIES, color_primaries);

    // Cleanup
    aom_codec_destroy(&codec);
    return 0;
}