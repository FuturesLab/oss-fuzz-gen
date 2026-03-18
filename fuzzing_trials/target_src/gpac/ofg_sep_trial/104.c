#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (the_file == NULL) {
        return 0;
    }

    // Ensure that size is sufficient to extract the required parameters
    if (size < 12) {
        gf_isom_close(the_file);
        return 0;
    }

    // Extract parameters from the input data
    u32 trackNumber = (u32)data[0] | ((u32)data[1] << 8) | ((u32)data[2] << 16) | ((u32)data[3] << 24);
    u32 referenceType = (u32)data[4] | ((u32)data[5] << 8) | ((u32)data[6] << 16) | ((u32)data[7] << 24);
    GF_ISOTrackID ReferencedTrackID = (GF_ISOTrackID)data[8] | ((GF_ISOTrackID)data[9] << 8) | ((GF_ISOTrackID)data[10] << 16) | ((GF_ISOTrackID)data[11] << 24);

    // Call the function-under-test
    gf_isom_set_track_reference(the_file, trackNumber, referenceType, ReferencedTrackID);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}