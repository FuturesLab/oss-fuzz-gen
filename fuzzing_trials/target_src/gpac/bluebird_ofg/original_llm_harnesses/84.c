#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = (size > 0) ? data[0] : 1; // Ensure trackNumber is valid
    u64 EditTime = (size > 1) ? data[1] : 0;
    u64 EditDuration = (size > 2) ? data[2] : 0;
    u64 MediaTime = (size > 3) ? data[3] : 0;
    GF_ISOEditType EditMode = (size > 4) ? (GF_ISOEditType)data[4] : GF_ISOM_EDIT_NORMAL; // Corrected constant name

    gf_isom_set_edit(movie, trackNumber, EditTime, EditDuration, MediaTime, EditMode);

    gf_isom_close(movie);
    return 0;
}