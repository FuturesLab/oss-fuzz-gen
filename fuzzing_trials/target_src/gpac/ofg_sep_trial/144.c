#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Ensure the input data is not null and has a minimum size
    if (data == NULL || size < 1) {
        return 0;
    }

    // Initialize parameters for the function-under-test
    GF_ISOFile *the_file = gf_isom_open("test.mp4", GF_ISOM_OPEN_READ, NULL); // Open a test file
    if (the_file == NULL) {
        return 0;
    }

    u32 trackNumber = 1; // Assuming track 1 for testing
    u32 sampleNumber = 1; // Assuming sample 1 for testing
    u32 sampleDescIndex = 1; // Assuming sample description index 1 for testing
    u32 container_type = 0;
    u8 *out_buffer = NULL;
    u32 outSize = 0;

    // Call the function-under-test
    gf_isom_cenc_get_sample_aux_info(the_file, trackNumber, sampleNumber, sampleDescIndex, &container_type, &out_buffer, &outSize);

    // Clean up
    if (out_buffer != NULL) {
        free(out_buffer);
    }
    gf_isom_close(the_file);

    return 0;
}