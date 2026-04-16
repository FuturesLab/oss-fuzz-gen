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
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aom.h"
#include "/src/aom/aom/aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_enc_cfg_t)) {
        return 0;
    }

    // Prepare encoder configuration
    aom_codec_enc_cfg_t cfg;
    memcpy(&cfg, Data, sizeof(cfg));

    // Initialize codec context
    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));

    // Initialize encoder interface
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (!iface) {
        return 0;
    }

    // Initialize the encoder
    aom_codec_err_t res = aom_codec_enc_init_ver(&codec, iface, &cfg, 0, AOM_ENCODER_ABI_VERSION);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Set active map
    aom_active_map_t active_map;
    active_map.rows = 1;
    active_map.active_map = new unsigned char[1];
    active_map.active_map[0] = 1;
    res = aom_codec_control(&codec, AOME_SET_ACTIVEMAP, &active_map);
    delete[] active_map.active_map;

    // Set ROI map
    aom_roi_map_t roi_map;
    roi_map.enabled = 1;
    roi_map.rows = 1;
    roi_map.roi_map = new unsigned char[1];
    roi_map.roi_map[0] = 0;
    res = aom_codec_control(&codec, AOME_SET_ROI_MAP, &roi_map);
    delete[] roi_map.roi_map;

    // Get last quantizer
    int last_quantizer;
    res = aom_codec_control(&codec, AOME_GET_LAST_QUANTIZER, &last_quantizer);

    // Set tile rows
    int tile_rows = 2;
    res = aom_codec_control(&codec, AV1E_SET_TILE_ROWS, tile_rows);

    // Get active map
    aom_active_map_t retrieved_active_map;
    res = aom_codec_control(&codec, AV1E_GET_ACTIVEMAP, &retrieved_active_map);

    // Cleanup
    aom_codec_destroy(&codec);

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

    LLVMFuzzerTestOneInput_10(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
