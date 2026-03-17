#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_334(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract necessary parameters
    if (size < sizeof(GF_ISOTrackID) + sizeof(Bool) * 3) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *output = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!output) {
        return 0;
    }

    // Extract parameters from input data
    GF_ISOTrackID TrackID = *(GF_ISOTrackID *)data;
    data += sizeof(GF_ISOTrackID);
    size -= sizeof(GF_ISOTrackID);

    u8 *sai_b = (u8 *)data;
    u32 sai_b_size = size;

    Bool use_subsamples = (Bool)*(data + size - 3);
    Bool use_saio_32bit = (Bool)*(data + size - 2);
    Bool use_multikey = (Bool)*(data + size - 1);

    // Call the function-under-test
    gf_isom_fragment_set_cenc_sai(output, TrackID, sai_b, sai_b_size, use_subsamples, use_saio_32bit, use_multikey);

    // Clean up
    gf_isom_close(output);

    return 0;
}