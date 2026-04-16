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
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "/src/aom/aom/aom_integer.h"
#include "/src/aom/aom/aom_image.h"
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aom_frame_buffer.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aom_external_partition.h"
#include "/src/aom/aom/aom.h"
#include "/src/aom/aom/aomcx.h"
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) {
        return 0;
    }

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
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_img_add_metadata to aom_img_get_metadata
        const aom_metadata_t* ret_aom_img_get_metadata_uqntx = aom_img_get_metadata(&img, AOM_PLANE_V);
        if (ret_aom_img_get_metadata_uqntx == NULL){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
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

    LLVMFuzzerTestOneInput_17(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
