#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (file == NULL) {
        return 0;
    }

    u32 track = 1; // Assuming track 1 for testing
    u32 sampleDescriptionIndex = 1; // Assuming the first sample description index

    // Ensure that data is not NULL and size is non-zero
    if (size > 0) {
        gf_isom_update_sample_description_from_template(file, track, sampleDescriptionIndex, (u8 *)data, (u32)size);
    }

    gf_isom_close(file);
    return 0;
}