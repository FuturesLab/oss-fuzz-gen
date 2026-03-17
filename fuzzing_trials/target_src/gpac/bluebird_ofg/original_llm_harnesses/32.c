#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) return 0;

    u32 trackNumber = 1; // Example track number
    u32 StreamDescriptionIndex = 1; // Example stream description index

    // Create a dummy descriptor for testing
    GF_Descriptor *theDesc = gf_odf_desc_new(0x03); // Using 0x03 as a generic tag for testing
    if (!theDesc) {
        gf_isom_close(movie);
        return 0;
    }

    // Call the function-under-test
    gf_isom_add_desc_to_description(movie, trackNumber, StreamDescriptionIndex, theDesc);

    // Clean up
    gf_odf_desc_del(theDesc);
    gf_isom_close(movie);

    return 0;
}