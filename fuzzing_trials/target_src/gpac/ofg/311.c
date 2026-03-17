#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_311(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the parameters
    if (size < sizeof(GF_ISOiTunesTag) + sizeof(u32) + sizeof(u64) + sizeof(u32)) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *mov = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!mov) {
        return 0;
    }

    // Extract parameters from the input data
    GF_ISOiTunesTag tag = *(GF_ISOiTunesTag *)data;
    data += sizeof(GF_ISOiTunesTag);

    u32 data_len = *(u32 *)data;
    data += sizeof(u32);

    u64 int_val = *(u64 *)data;
    data += sizeof(u64);

    u32 int_val2 = *(u32 *)data;
    data += sizeof(u32);

    // Ensure data_len does not exceed remaining available data
    if (data_len > size - (data - (const uint8_t *)data)) {
        data_len = size - (data - (const uint8_t *)data);
    }

    // Call the function-under-test
    gf_isom_apple_set_tag(mov, tag, data, data_len, int_val, int_val2);

    // Close the ISO file
    gf_isom_close(mov);

    return 0;
}