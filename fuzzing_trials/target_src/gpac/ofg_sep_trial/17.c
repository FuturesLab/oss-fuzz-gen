#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    GF_ISOFile *orig_file = gf_isom_open("orig.mp4", GF_ISOM_OPEN_READ, NULL);
    GF_ISOFile *dest_file = gf_isom_open("dest.mp4", GF_ISOM_OPEN_WRITE, NULL);

    if (!orig_file || !dest_file) {
        if (orig_file) gf_isom_close(orig_file);
        if (dest_file) gf_isom_close(dest_file);
        return 0;
    }

    u32 orig_track = 1; // Assuming track 1 for fuzzing
    GF_ISOTrackCloneFlags flags = GF_ISOM_CLONE_TRACK_NO_QT; // Corrected flag
    u32 dest_track;

    gf_isom_clone_track(orig_file, orig_track, dest_file, flags, &dest_track);

    gf_isom_close(orig_file);
    gf_isom_close(dest_file);

    return 0;
}