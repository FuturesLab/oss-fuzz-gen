// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_add_metadata at aom_image.c:380:5 in aom_image.h
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

static aom_image_t* create_image(size_t width, size_t height) {
    aom_image_t* img = (aom_image_t*)malloc(sizeof(aom_image_t));
    if (!img) return nullptr;

    img->w = width;
    img->h = height;
    img->fmt = AOM_IMG_FMT_I420; // Example format
    img->metadata = nullptr; // Initialize metadata to null
    // Allocate planes
    for (int i = 0; i < 3; ++i) {
        img->planes[i] = (unsigned char*)malloc(width * height);
        img->stride[i] = width;
    }
    return img;
}

static void free_image(aom_image_t* img) {
    if (img) {
        for (int i = 0; i < 3; ++i) {
            free(img->planes[i]);
        }
        free(img);
    }
}

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0; // Minimum size to create a valid image

    // Prepare environment
    size_t width = Data[0] % 1024 + 1; // Width between 1 and 1024
    size_t height = Data[1] % 1024 + 1; // Height between 1 and 1024
    aom_image_t* img = create_image(width, height);

    // Fuzzing various API functions
    if (img) {
        // Test aom_img_add_metadata
        uint32_t type = Data[2] % 10; // Example type
        const uint8_t* metadata_data = Data + 3;
        size_t metadata_size = Size - 3;
        aom_metadata_insert_flags_t insert_flag = static_cast<aom_metadata_insert_flags_t>(Data[4] % 6);
        aom_img_add_metadata(img, type, metadata_data, metadata_size, insert_flag);

        // Test aom_img_num_metadata
        size_t num_metadata = aom_img_num_metadata(img);

        // Test aom_img_get_metadata
        const aom_metadata_t* metadata = aom_img_get_metadata(img, Data[5] % num_metadata);

        // Test aom_img_remove_metadata
        aom_img_remove_metadata(img);

        // Clean up
        free_image(img);
    }

    return 0;
}