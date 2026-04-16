#include <string.h>
#include <sys/stat.h>
#include <cstddef>
#include <cstdint>
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    aom_codec_ctx_t codec;
    aom_codec_err_t res;
    aom_codec_iface_t *iface = aom_codec_av1_dx(); // Use AV1 decoder interface
    void *user_priv = (void*)1; // Non-NULL user private data

    // Initialize the codec context
    res = aom_codec_dec_init(&codec, iface, NULL, 0);
    if (res != AOM_CODEC_OK) {
        return 0; // Initialization failed
    }

    // Call the function-under-test
    res = aom_codec_decode(&codec, data, size, user_priv);

    // Destroy the codec context

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_decode to aom_codec_set_frame_buffer_functions
    aom_image_t itwfpvem;
    memset(&itwfpvem, 0, sizeof(itwfpvem));
    aom_img_flip(&itwfpvem);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_img_flip to aom_img_set_rect
    aom_codec_caps_t ret_aom_codec_get_caps_qpslb = aom_codec_get_caps(iface);
    if (ret_aom_codec_get_caps_qpslb < 0){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_get_caps to aom_uleb_encode_fixed_size
    size_t ret_aom_uleb_size_in_bytes_htijk = aom_uleb_size_in_bytes(AOM_PLANE_U);
    if (ret_aom_uleb_size_in_bytes_htijk < 0){
    	return 0;
    }
    size_t ret_aom_uleb_size_in_bytes_lxdgc = aom_uleb_size_in_bytes(AOM_PLANE_V);
    if (ret_aom_uleb_size_in_bytes_lxdgc < 0){
    	return 0;
    }
    size_t ret_aom_uleb_size_in_bytes_gqgre = aom_uleb_size_in_bytes(64);
    if (ret_aom_uleb_size_in_bytes_gqgre < 0){
    	return 0;
    }
    size_t ret_aom_img_num_metadata_rrxae = aom_img_num_metadata(NULL);
    if (ret_aom_img_num_metadata_rrxae < 0){
    	return 0;
    }
    int ret_aom_uleb_encode_fixed_size_hteie = aom_uleb_encode_fixed_size((uint64_t )ret_aom_codec_get_caps_qpslb, ret_aom_uleb_size_in_bytes_htijk, ret_aom_uleb_size_in_bytes_lxdgc, (uint8_t *)&ret_aom_uleb_size_in_bytes_gqgre, &ret_aom_img_num_metadata_rrxae);
    if (ret_aom_uleb_encode_fixed_size_hteie < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    size_t ret_aom_uleb_size_in_bytes_tycyt = aom_uleb_size_in_bytes(AOM_MAX_TILE_ROWS);
    if (ret_aom_uleb_size_in_bytes_tycyt < 0){
    	return 0;
    }
    int ret_aom_img_set_rect_nxrsl = aom_img_set_rect(&itwfpvem, 64, (unsigned int )ret_aom_codec_get_caps_qpslb, 64, (unsigned int )ret_aom_uleb_size_in_bytes_tycyt, AOM_MAX_TILE_ROWS);
    if (ret_aom_img_set_rect_nxrsl < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    aom_codec_err_t ret_aom_codec_set_frame_buffer_functions_ydahc = aom_codec_set_frame_buffer_functions(&codec, 0, 0, (void *)&itwfpvem);
    // End mutation: Producer.APPEND_MUTATOR
    
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

    LLVMFuzzerTestOneInput_9(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
