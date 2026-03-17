#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0; // Exit if movie creation fails
    }

    u32 trackNumber = 1; // Example track number
    u32 StreamDescriptionIndex = 1; // Example stream description index

    // Create a dummy descriptor
    GF_Descriptor *theDesc = (GF_Descriptor *) malloc(sizeof(GF_Descriptor));
    if (!theDesc) {
        gf_isom_close(movie);
        return 0; // Exit if descriptor allocation fails
    }
    theDesc->tag = GF_ODF_ESD_TAG; // Example tag

    // Call the function-under-test
    gf_isom_add_desc_to_description(movie, trackNumber, StreamDescriptionIndex, theDesc);

    // Clean up
    free(theDesc);
    gf_isom_close(movie);

    return 0;
}