#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_216(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;
    u32 StreamDescriptionIndex = 1;

    // Manually allocate and initialize a new GF_ESD structure
    GF_ESD *newESD = (GF_ESD *)malloc(sizeof(GF_ESD));
    if (newESD == NULL) {
        gf_isom_close(movie);
        return 0;
    }

    // Set some values in newESD to avoid NULL dereference
    newESD->ESID = 1;
    newESD->decoderConfig = (GF_DecoderConfig *)malloc(sizeof(GF_DecoderConfig));
    if (newESD->decoderConfig == NULL) {
        gf_isom_close(movie);
        free(newESD);
        return 0;
    }
    newESD->decoderConfig->objectTypeIndication = 0x40; // Example value

    // Call the function-under-test
    gf_isom_change_mpeg4_description(movie, trackNumber, StreamDescriptionIndex, newESD);

    // Clean up
    free(newESD->decoderConfig);
    free(newESD);
    gf_isom_close(movie);

    return 0;
}