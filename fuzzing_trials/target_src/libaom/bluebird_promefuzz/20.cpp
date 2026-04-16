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
#include "/src/aom/aom/aomcx.h"
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aom_external_partition.h"
#include "/src/aom/aom/aom_frame_buffer.h"
#include "/src/aom/aom/aom_image.h"
#include "/src/aom/aom/aom_integer.h"

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize decoder
    aom_codec_ctx_t dec_ctx;
    aom_codec_iface_t *dec_iface = aom_codec_av1_dx();

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_av1_dx to aom_codec_peek_stream_info
    size_t ret_aom_uleb_size_in_bytes_vffau = aom_uleb_size_in_bytes(Size);
    if (ret_aom_uleb_size_in_bytes_vffau < 0){
    	return 0;
    }
    aom_codec_err_t ret_aom_codec_peek_stream_info_zlcgo = aom_codec_peek_stream_info(dec_iface, (const uint8_t *)&ret_aom_uleb_size_in_bytes_vffau, AOM_MAX_SEGMENTS, NULL);
    // End mutation: Producer.APPEND_MUTATOR
    
    aom_codec_dec_cfg_t dec_cfg = {0}; // Default configuration
    aom_codec_err_t dec_res = aom_codec_dec_init_ver(&dec_ctx, dec_iface, &dec_cfg, 0, AOM_DECODER_ABI_VERSION);
    if (dec_res != AOM_CODEC_OK) {
        return 0;
    }

    // Initialize encoder
    aom_codec_ctx_t enc_ctx;
    aom_codec_iface_t *enc_iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t enc_cfg;
    if (aom_codec_enc_config_default(enc_iface, &enc_cfg, 0) != AOM_CODEC_OK) {
        aom_codec_destroy(&dec_ctx);
        return 0;
    }
    aom_codec_err_t enc_res = aom_codec_enc_init_ver(&enc_ctx, enc_iface, &enc_cfg, 0, AOM_ENCODER_ABI_VERSION);
    if (enc_res != AOM_CODEC_OK) {
        aom_codec_destroy(&dec_ctx);
        return 0;
    }

    // Decode input data
    if (aom_codec_decode(&dec_ctx, Data, Size, NULL) != AOM_CODEC_OK) {
        aom_codec_destroy(&enc_ctx);
        aom_codec_destroy(&dec_ctx);
        return 0;
    }

    // Get decoded frames
    aom_codec_iter_t iter = NULL;
    aom_image_t *img = nullptr;
    while ((img = aom_codec_get_frame(&dec_ctx, &iter)) != NULL) {
        // Encode the frame
        if (aom_codec_encode(&enc_ctx, img, 0, 1, 0) != AOM_CODEC_OK) {
            break;
        }

        // Get stream info
        aom_codec_stream_info_t si;
        if (aom_codec_get_stream_info(&dec_ctx, &si) != AOM_CODEC_OK) {
            break;
        }

        // Get capabilities
        aom_codec_caps_t caps = aom_codec_get_caps(dec_iface);

        (void)caps; // Use capabilities for something meaningful
    }

    // Cleanup
    aom_codec_destroy(&enc_ctx);
    aom_codec_destroy(&dec_ctx);

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

    LLVMFuzzerTestOneInput_20(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
