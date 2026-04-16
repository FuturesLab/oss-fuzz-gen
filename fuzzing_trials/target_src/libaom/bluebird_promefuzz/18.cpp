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
#include "/src/aom/aom/aom.h"
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aomcx.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aom_external_partition.h"
#include "/src/aom/aom/aom_frame_buffer.h"
#include "/src/aom/aom/aom_image.h"
#include "/src/aom/aom/aom_integer.h"
#include "aom/aomdx.h"
#include "aom/aom_decoder.h"

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    // Initialize codec context
    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    if (aom_codec_enc_config_default(iface, &cfg, 0)) {
        return 0;
    }

    if (aom_codec_enc_init(&codec, iface, &cfg, 0)) {
        return 0;
    }

    // Prepare parameters from input data
    int bitrate = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_BITRATE_ONE_PASS_CBR
    aom_codec_control(&codec, AV1E_SET_BITRATE_ONE_PASS_CBR, bitrate);

    if (Size < 1) {
        aom_codec_destroy(&codec);
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_ENABLE_RATE_GUIDE_DELTAQ
    int enable_rate_guide_deltaq = Data[0] % 2;
    aom_codec_control(&codec, AV1E_ENABLE_RATE_GUIDE_DELTAQ, enable_rate_guide_deltaq);

    if (Size < 2) {
        aom_codec_destroy(&codec);
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING
    int enable_keyframe_filtering = Data[1] % 2;
    aom_codec_control(&codec, AV1E_SET_ENABLE_KEYFRAME_FILTERING, enable_keyframe_filtering);

    if (Size < 3) {
        aom_codec_destroy(&codec);
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE
    int force_video_mode = Data[2] % 2;
    aom_codec_control(&codec, AV1E_SET_FORCE_VIDEO_MODE, force_video_mode);

    if (Size < 4) {
        aom_codec_destroy(&codec);
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_AUTO_TILES

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_control to aom_codec_error_detail
    const char* ret_aom_codec_error_detail_ukxjw = aom_codec_error_detail(&codec);
    if (ret_aom_codec_error_detail_ukxjw == NULL){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    int auto_tiles = Data[3] % 2;
    aom_codec_control(&codec, AV1E_SET_AUTO_TILES, auto_tiles);

    if (Size < 5) {
        aom_codec_destroy(&codec);
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_AQ_MODE
    int aq_mode = Data[4] % 4; // Assuming 4 different AQ modes
    aom_codec_control(&codec, AV1E_SET_AQ_MODE, aq_mode);

    // Clean up
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

    LLVMFuzzerTestOneInput_18(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
