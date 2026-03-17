#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the parameters
    if (size < sizeof(uint32_t) * 3) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    GF_ISOFile *the_file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract parameters from the input data
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t referenceType = *((uint32_t *)(data + sizeof(uint32_t)));
    GF_ISOTrackID ReferencedTrackID = *((GF_ISOTrackID *)(data + sizeof(uint32_t) * 2));

    // Call the function-under-test
    gf_isom_set_track_reference(the_file, trackNumber, referenceType, ReferencedTrackID);

    // Cleanup
    gf_isom_close(the_file);

    return 0;
}