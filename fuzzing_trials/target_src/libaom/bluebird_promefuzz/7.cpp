#include <string.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aomcx.h"
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>

static void initialize_codec(aom_codec_ctx_t *codec_ctx, aom_codec_iface_t *iface) {
    aom_codec_enc_cfg_t cfg;
    if (aom_codec_enc_config_default(iface, &cfg, 0) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to get default codec config.\n");
        exit(1);
    }

    if (aom_codec_enc_init(codec_ctx, iface, &cfg, 0) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to initialize codec.\n");
        exit(1);
    }
}

static void cleanup_codec(aom_codec_ctx_t *codec_ctx) {
    if (aom_codec_destroy(codec_ctx) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to destroy codec.\n");
    }
}

static void fuzz_codec_controls(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    int cq_level = Data[0] % 64; // CQ level range
    if (aom_codec_control(codec_ctx, AOME_SET_CQ_LEVEL, cq_level) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to set CQ level.\n");
    }

    if (Size < 2) return;
    int enable_auto_alt_ref = Data[1] % 2;
    if (aom_codec_control(codec_ctx, AOME_SET_ENABLEAUTOALTREF, enable_auto_alt_ref) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to set auto alt ref.\n");
    }

    if (Size < 3) return;
    int num_spatial_layers = Data[2] % 5 + 1; // 1 to 5 layers
    if (aom_codec_control(codec_ctx, AOME_SET_NUMBER_SPATIAL_LAYERS, num_spatial_layers) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to set number of spatial layers.\n");
    }

    int loop_filter_level;
    if (aom_codec_control(codec_ctx, AOME_GET_LOOPFILTER_LEVEL, &loop_filter_level) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to get loop filter level.\n");
    }

    if (Size < 4) return;
    int arnr_max_frames = Data[3] % 16; // ARNR max frames range
    if (aom_codec_control(codec_ctx, AOME_SET_ARNR_MAXFRAMES, arnr_max_frames) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to set ARNR max frames.\n");
    }

    if (Size < 5) return;
    int sharpness = Data[4] % 8; // Sharpness range
    if (aom_codec_control(codec_ctx, AOME_SET_SHARPNESS, sharpness) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to set sharpness.\n");
    }
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();

    initialize_codec(&codec_ctx, iface);
    fuzz_codec_controls(&codec_ctx, Data, Size);
    cleanup_codec(&codec_ctx);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_7(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
