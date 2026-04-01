#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_EDIT, NULL);
    u32 trackNumber = 1;  // Assuming track number 1 for fuzzing
    u32 StreamDescriptionIndex = 1;  // Assuming stream description index 1 for fuzzing

    // Ensure movie is not NULL
    if (!movie) {
        return 0;
    }

    // Create a new ESD
    GF_ESD *newESD = gf_odf_new_esd();
    if (!newESD) {
        gf_isom_close(movie);
        return 0;
    }

    // Fuzz the ESD with input data
    if (size > 0) {
        newESD->ESID = data[0];  // Use the first byte as ESID
    }

    // Call the function under test
    gf_isom_change_mpeg4_description(movie, trackNumber, StreamDescriptionIndex, newESD);

    // Clean up
    gf_isom_close(movie);
    gf_odf_desc_del((GF_Descriptor *)newESD);

    return 0;
}