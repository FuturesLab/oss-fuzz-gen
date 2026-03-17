#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Initialize the GF_ISOFile and GF_Descriptor structures
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0; // Exit if the movie could not be created
    }

    // Allocate memory for GF_Descriptor and initialize it
    GF_Descriptor *theDesc = (GF_Descriptor *)malloc(sizeof(GF_Descriptor));
    if (!theDesc) {
        gf_isom_close(movie);
        return 0; // Exit if memory allocation fails
    }

    // For fuzzing purposes, populate the descriptor with data
    // Here we simply copy the input data to the descriptor's fields
    // In a real scenario, you should ensure the descriptor is valid and meaningful
    if (size >= sizeof(GF_Descriptor)) {
        memcpy(theDesc, data, sizeof(GF_Descriptor));
    } else {
        free(theDesc);
        gf_isom_close(movie);
        return 0; // Exit if the input size is insufficient
    }

    // Call the function-under-test
    gf_isom_add_desc_to_root_od(movie, theDesc);

    // Clean up
    free(theDesc);
    gf_isom_close(movie);

    return 0;
}