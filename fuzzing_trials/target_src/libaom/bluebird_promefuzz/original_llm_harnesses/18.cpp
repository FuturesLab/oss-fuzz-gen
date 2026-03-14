// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_uleb_size_in_bytes at aom_integer.c:23:8 in aom_integer.h
// aom_uleb_encode at aom_integer.c:58:5 in aom_integer.h
// aom_uleb_encode_fixed_size at aom_integer.c:79:5 in aom_integer.h
// aom_img_add_metadata at aom_image.c:380:5 in aom_image.h
// aom_img_num_metadata at aom_image.c:429:8 in aom_image.h
// aom_uleb_decode at aom_integer.c:31:5 in aom_integer.h
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

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return 0;

    // Test aom_uleb_encode
    {
        uint64_t value;
        memcpy(&value, Data, sizeof(uint64_t));
        size_t available = Size - sizeof(uint64_t);
        uint8_t *coded_value = new uint8_t[available];
        size_t coded_size = 0;

        int result = aom_uleb_encode(value, available, coded_value, &coded_size);
        if (result == 0) {
            // Successfully encoded
        } else {
            // Encoding failed
        }
        delete[] coded_value;
    }

    // Test aom_uleb_encode_fixed_size
    {
        uint64_t value;
        memcpy(&value, Data, sizeof(uint64_t));
        size_t available = Size - sizeof(uint64_t);
        size_t pad_to_size = available > 0 ? available : 1; // Ensure non-zero pad size
        uint8_t *coded_value = new uint8_t[pad_to_size];
        size_t coded_size = 0;

        int result = aom_uleb_encode_fixed_size(value, available, pad_to_size, coded_value, &coded_size);
        if (result == 0) {
            // Successfully encoded
        } else {
            // Encoding failed
        }
        delete[] coded_value;
    }

    // Test aom_img_add_metadata
    {
        aom_image_t img;
        memset(&img, 0, sizeof(img));
        uint32_t type = 0;
        const uint8_t *data = Data;
        size_t sz = Size;
        aom_metadata_insert_flags_t insert_flag = AOM_MIF_ANY_FRAME;

        int result = aom_img_add_metadata(&img, type, data, sz, insert_flag);
        if (result == 0) {
            // Metadata successfully added
        } else {
            // Failed to add metadata
        }
    }

    // Test aom_img_num_metadata
    {
        aom_image_t img;
        memset(&img, 0, sizeof(img));

        size_t num_metadata = aom_img_num_metadata(&img);
        // Use num_metadata for further logic
    }

    // Test aom_uleb_decode
    {
        uint64_t decoded_value = 0;
        size_t length = 0;
        int result = aom_uleb_decode(Data, Size, &decoded_value, &length);
        if (result == 0) {
            // Successfully decoded
        } else {
            // Decoding failed
        }
    }

    // Test aom_uleb_size_in_bytes
    {
        uint64_t value;
        memcpy(&value, Data, sizeof(uint64_t));
        size_t size_in_bytes = aom_uleb_size_in_bytes(value);
        // Use size_in_bytes for further logic
    }

    return 0;
}