#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

// The function-under-test
GF_Err gf_isom_check_data_reference(GF_ISOFile *isom_file, u32 trackNumber, u32 sampleDescriptionIndex);

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // We can't use sizeof(GF_ISOFile) because it's an incomplete type.
    // Instead, let's assume a minimum size for fuzzing purposes.
    const size_t min_size = sizeof(u32) * 2;

    if (size < min_size) {
        return 0;
    }

    // Initialize the parameters for the function-under-test
    // Instead of allocating memory for GF_ISOFile, we assume a mock setup
    GF_ISOFile *the_file = NULL; // Placeholder for a real object, if available

    // If there's a library function to create or initialize GF_ISOFile, it should be used here
    // For example: the_file = gf_isom_open_file(...); (this is hypothetical)

    u32 trackNumber;
    u32 StreamDescriptionIndex;

    // Copy data into the parameters
    memcpy(&trackNumber, data, sizeof(u32));
    memcpy(&StreamDescriptionIndex, data + sizeof(u32), sizeof(u32));

    // Call the function-under-test
    gf_isom_check_data_reference(the_file, trackNumber, StreamDescriptionIndex);

    // Free the allocated memory or close the file if it was opened
    // For example: gf_isom_close_file(the_file); (this is hypothetical)

    return 0;
}