#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_269(const uint8_t *data, size_t size) {
    // Declare variables
    GF_ISOFile *src = NULL;
    GF_ISOFile *dst = NULL;
    u32 src_track = 1;
    u32 dst_track = 1;
    u32 sampleNumber = 1;

    // Initialize source and destination ISO files
    src = gf_isom_open("source.mp4", GF_ISOM_OPEN_READ, NULL);
    dst = gf_isom_open("destination.mp4", GF_ISOM_OPEN_WRITE, NULL);

    // Check if files are opened successfully
    if (src == NULL || dst == NULL) {
        if (src != NULL) gf_isom_close(src);
        if (dst != NULL) gf_isom_close(dst);
        return 0;
    }

    // Call the function-under-test
    gf_isom_copy_sample_info(dst, dst_track, src, src_track, sampleNumber);

    // Clean up
    gf_isom_close(src);
    gf_isom_close(dst);

    return 0;
}