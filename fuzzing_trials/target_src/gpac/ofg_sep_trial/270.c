#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_270(const uint8_t *data, size_t size) {
    GF_ISOFile *src = gf_isom_open("src.mp4", GF_ISOM_OPEN_READ, NULL);
    GF_ISOFile *dst = gf_isom_open("dst.mp4", GF_ISOM_OPEN_WRITE, NULL);

    if (!src || !dst) {
        if (src) gf_isom_close(src);
        if (dst) gf_isom_close(dst);
        return 0;
    }

    u32 src_track = 1;
    u32 dst_track = 1;
    u32 sampleNumber = 1;

    if (size >= 12) {
        src_track = ((u32 *)data)[0];
        dst_track = ((u32 *)data)[1];
        sampleNumber = ((u32 *)data)[2];
    }

    gf_isom_copy_sample_info(dst, dst_track, src, src_track, sampleNumber);

    gf_isom_close(src);
    gf_isom_close(dst);

    return 0;
}