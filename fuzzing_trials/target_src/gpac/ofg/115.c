#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Initialize a GF_ISOFile structure using an alternative valid function
    GF_ISOFile *file = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);

    // Ensure the file is not NULL
    if (file == NULL) {
        return 0;
    }

    // Define a Bool variable for the set_on parameter
    Bool set_on = (size % 2 == 0) ? 1 : 0; // Arbitrarily set based on size

    // Call the function-under-test
    gf_isom_force_64bit_chunk_offset(file, set_on);

    // Close the file to free resources
    gf_isom_close(file);

    return 0;
}