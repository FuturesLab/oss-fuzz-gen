// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_num_metadata at aom_image.c:429:8 in aom_image.h
// aom_img_get_metadata at aom_image.c:419:23 in aom_image.h
// aom_img_metadata_free at aom_image.c:345:6 in aom_image.h
// aom_img_metadata_alloc at aom_image.c:327:17 in aom_image.h
// aom_img_add_metadata at aom_image.c:380:5 in aom_image.h
// aom_img_metadata_free at aom_image.c:345:6 in aom_image.h
// aom_img_remove_metadata at aom_image.c:412:6 in aom_image.h
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
#include <cstdlib>
#include <cstring>
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

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    // Prepare environment
    aom_image_t img;
    memset(&img, 0, sizeof(img));
    img.fmt = AOM_IMG_FMT_I420; // Set a valid image format
    img.w = 640; // Set width
    img.h = 480; // Set height
    img.planes[0] = (unsigned char*)malloc(img.w * img.h); // Allocate memory for Y plane
    img.planes[1] = (unsigned char*)malloc(img.w * img.h / 4); // Allocate memory for U plane
    img.planes[2] = (unsigned char*)malloc(img.w * img.h / 4); // Allocate memory for V plane
    img.metadata = nullptr; // Initialize metadata pointer

    // Fuzzing logic
    size_t num_metadata = aom_img_num_metadata(&img);
    if (num_metadata > 0) {
        const aom_metadata_t *metadata = aom_img_get_metadata(&img, 0);
        if (metadata) {
            aom_img_metadata_free((aom_metadata_t*)metadata);
        }
    }
    
    // Adding metadata
    if (Size > 0) {
        aom_metadata_t *metadata = aom_img_metadata_alloc(1, Data, Size, AOM_MIF_ANY_FRAME);
        if (metadata) {
            aom_img_add_metadata(&img, metadata->type, metadata->payload, metadata->sz, metadata->insert_flag);
            aom_img_metadata_free(metadata);
        }
    }

    // Cleanup
    aom_img_remove_metadata(&img);
    free(img.planes[0]);
    free(img.planes[1]);
    free(img.planes[2]);

    return 0;
}