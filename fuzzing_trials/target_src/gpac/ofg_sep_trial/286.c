#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Include necessary headers for the GPAC library
#include <gpac/isomedia.h>
#include <gpac/constants.h>
#include <gpac/internal/isomedia_dev.h>

// Correct the path to the function declaration if needed
// #include "/src/gpac/src/isomedia/sample_descs.c"

// Remove the extern "C" as it's not needed in C code
int LLVMFuzzerTestOneInput_286(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    GF_ISOFile *movie = (GF_ISOFile *)malloc(sizeof(GF_ISOFile));
    GF_DIMSDescription *desc = (GF_DIMSDescription *)malloc(sizeof(GF_DIMSDescription));
    u32 trackNumber = 1; // Example track number
    char URLname[256];
    char URNname[256];
    u32 outDescriptionIndex = 0;

    // Ensure movie and desc are not NULL
    if (movie == NULL || desc == NULL) {
        free(movie);
        free(desc);
        return 0;
    }

    // Initialize URLname and URNname with data if size is sufficient
    if (size > 0) {
        size_t copy_size = size < 255 ? size : 255;
        memcpy(URLname, data, copy_size);
        URLname[copy_size] = '\0'; // Null-terminate the string
        memcpy(URNname, data, copy_size);
        URNname[copy_size] = '\0'; // Null-terminate the string
    } else {
        strcpy(URLname, "http://example.com");
        strcpy(URNname, "urn:example");
    }

    // Call the function-under-test
    gf_isom_new_dims_description(movie, trackNumber, desc, (const char *)URLname, (const char *)URNname, &outDescriptionIndex);

    // Free allocated memory
    free(movie);
    free(desc);

    return 0;
}