// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_metadata_alloc at aom_image.c:327:17 in aom_image.h
// aom_img_metadata_free at aom_image.c:345:6 in aom_image.h
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
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "aom_integer.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom_frame_buffer.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom.h"
#include "aomcx.h"
#include "aom_decoder.h"
#include "aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy metadata
    uint32_t type = Data[0];
    const uint8_t *metadata_data = Data + 1;
    size_t metadata_size = Size - 1;
    aom_metadata_insert_flags_t insert_flag = AOM_MIF_ANY_FRAME;

    // Allocate metadata
    aom_metadata_t *metadata = aom_img_metadata_alloc(type, metadata_data, metadata_size, insert_flag);
    if (metadata) {
        // Free metadata
        aom_img_metadata_free(metadata);
    }

    // Prepare dummy image
    aom_image_t img;
    memset(&img, 0, sizeof(img));
    img.metadata = nullptr;

    // Add metadata to image
    int result = aom_img_add_metadata(&img, type, metadata_data, metadata_size, insert_flag);
    if (result == 0) {
        // Get number of metadata
        size_t num_metadata = aom_img_num_metadata(&img);
        for (size_t i = 0; i < num_metadata; ++i) {
            const aom_metadata_t *retrieved_metadata = aom_img_get_metadata(&img, i);
            if (retrieved_metadata) {
                // Do something with the retrieved metadata
            }
        }

        // Remove metadata
        aom_img_remove_metadata(&img);
    }

    return 0;
}