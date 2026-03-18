#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

// Assuming GF_EXPORT is defined as an export macro, if not, define it as empty
#ifndef GF_EXPORT
#define GF_EXPORT
#endif

// Function prototype for the function-under-test
GF_EXPORT GF_Err gf_isom_evte_config_new(GF_ISOFile *the_file, u32 trackNumber, u32 *outDescriptionIndex);

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    // Initialize the parameters for gf_isom_evte_config_new
    GF_ISOFile *the_file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL); // Create a new ISO file in memory
    if (!the_file) {
        return 0; // Exit if file creation fails
    }

    u32 trackNumber = 1; // Example track number
    u32 outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_evte_config_new(the_file, trackNumber, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}