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
#include "aom.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t) + sizeof(int)) {
        return 0; // Not enough data to proceed
    }

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Initialize codec interface
    codec_ctx.iface = aom_codec_av1_cx();

    // Initialize codec context
    if (aom_codec_enc_init(&codec_ctx, codec_ctx.iface, nullptr, 0) != AOM_CODEC_OK) {
        return 0; // Failed to initialize codec
    }

    // Prepare dummy file for partition info path
    FILE* dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        aom_codec_destroy(&codec_ctx);
        return 0; // Failed to create dummy file
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    // Extract an integer value from input data
    int param_value;
    memcpy(&param_value, Data, sizeof(int));

    // Fuzzing the target functions
    aom_codec_control(&codec_ctx, AV1E_SET_PARTITION_INFO_PATH, "./dummy_file");
    aom_codec_control(&codec_ctx, AV1E_SET_RATE_DISTRIBUTION_INFO, &param_value);
    aom_codec_control(&codec_ctx, AV1E_SET_LOOPFILTER_CONTROL, &param_value);
    aom_codec_control(&codec_ctx, AV1E_SET_MATRIX_COEFFICIENTS, &param_value);
    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_TX_SIZE_SEARCH, &param_value);
    aom_codec_control(&codec_ctx, AV1E_SET_TRANSFER_CHARACTERISTICS, &param_value);

    // Cleanup
    aom_codec_destroy(&codec_ctx);
    return 0;
}