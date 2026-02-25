// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_QM at aomcx.h:2052:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE at aomcx.h:1995:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC at aomcx.h:2046:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_ENABLE_RATE_GUIDE_DELTAQ at aomcx.h:2350:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL at aomcx.h:2010:1 in aomcx.h
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
#include "aom.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aom_image.h"
#include "aom_frame_buffer.h"
#include "aom_integer.h"
#include "aomcx.h"
#include "aom_external_partition.h"

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0; // Ensure there's enough data

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx(); // Get AV1 codec interface

    // Initialize the codec context
    aom_codec_err_t res = aom_codec_enc_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Fuzzing various API functions with random data
    int command = Data[0] % 5; // Randomly select a command to test
    switch (command) {
        case 0: // Enable QM
            aom_codec_control_typechecked_AV1E_SET_ENABLE_QM(&codec, 0, Data[1] % 2);
            break;
        case 1: // Set CDF update mode
            aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE(&codec, 0, Data[1] % 3);
            break;
        case 2: // Enable OBMC
            aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC(&codec, 0, Data[1] % 2);
            break;
        case 3: // Enable rate guide deltaQ
            aom_codec_control_typechecked_AV1E_ENABLE_RATE_GUIDE_DELTAQ(&codec, 0, Data[1] % 2);
            break;
        case 4: // Set minimum GF interval
            aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL(&codec, 0, Data[1] % 100);
            break;
    }

    // Cleanup
    aom_codec_destroy(&codec);
    return 0;
}