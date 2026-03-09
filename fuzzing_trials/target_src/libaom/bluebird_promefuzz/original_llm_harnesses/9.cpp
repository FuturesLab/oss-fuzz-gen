// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_free at aom_image.c:304:6 in aom_image.h
// aom_img_add_metadata at aom_image.c:380:5 in aom_image.h
// aom_img_flip at aom_image.c:285:6 in aom_image.h
// aom_img_num_metadata at aom_image.c:429:8 in aom_image.h
// aom_img_get_metadata at aom_image.c:419:23 in aom_image.h
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
extern "C" {
#include <aom/aom_integer.h>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom_encoder.h>
#include <aom/aom_external_partition.h>
#include <aom/aom.h>
#include <aom/aomcx.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>
}

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>

static void initialize_image(aom_image_t &img) {
    img.fmt = AOM_IMG_FMT_I420;
    img.cp = AOM_CICP_CP_BT_709;
    img.tc = AOM_CICP_TC_BT_709;
    img.mc = AOM_CICP_MC_BT_709;
    img.monochrome = 0;
    img.csp = AOM_CSP_UNKNOWN;
    img.range = AOM_CR_FULL_RANGE;
    img.w = 640;
    img.planes[0] = nullptr;  // Y plane
    img.planes[1] = nullptr;  // U plane
    img.planes[2] = nullptr;  // V plane
    img.stride[0] = 640;
    img.stride[1] = 320;
    img.stride[2] = 320;
    img.sz = 640 * 480 + 2 * (320 * 240);
    img.img_data = new unsigned char[img.sz];
    img.metadata = nullptr;

    // Assign planes to point into img_data
    img.planes[0] = img.img_data;
    img.planes[1] = img.img_data + (640 * 480);
    img.planes[2] = img.img_data + (640 * 480) + (320 * 240);
}

static void cleanup_image(aom_image_t &img) {
    delete[] img.img_data;
    aom_img_free(&img);
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_image_t img;
    initialize_image(img);

    // Fuzz aom_img_add_metadata
    if (Size > 10) {
        uint32_t type = Data[0];
        size_t metadata_size = Size - 10;
        aom_metadata_insert_flags_t insert_flag = static_cast<aom_metadata_insert_flags_t>(Data[1] % 19);
        aom_img_add_metadata(&img, type, Data + 10, metadata_size, insert_flag);
    }

    // Fuzz aom_img_flip
    aom_img_flip(&img);

    // Fuzz aom_img_num_metadata
    size_t num_metadata = aom_img_num_metadata(&img);

    // Fuzz aom_img_get_metadata
    if (num_metadata > 0) {
        size_t index = Data[2] % num_metadata;
        const aom_metadata_t *metadata = aom_img_get_metadata(&img, index);
        (void)metadata;  // Use metadata in some way if needed
    }

    // Fuzz aom_img_remove_metadata
    aom_img_remove_metadata(&img);

    cleanup_image(img);
    return 0;
}