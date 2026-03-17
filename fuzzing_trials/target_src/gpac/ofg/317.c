#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_317(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL); // Create a dummy file
    if (!file) return 0; // Ensure file is not NULL

    u32 track = 1; // Set track to a valid non-zero value
    u32 sampleNumber = 1; // Set sampleNumber to a valid non-zero value
    u32 aux_type = 0; // Set aux_type to 0 for testing
    u32 aux_info = 0; // Set aux_info to 0 for testing

    // Ensure data is not NULL
    u8 *aux_data = (u8 *)malloc(size);
    if (!aux_data) {
        gf_isom_close(file);
        return 0;
    }
    memcpy(aux_data, data, size);

    // Call the function-under-test
    GF_Err result = gf_isom_add_sample_aux_info(file, track, sampleNumber, aux_type, aux_info, aux_data, (u32)size);

    // Clean up
    free(aux_data);
    gf_isom_close(file);

    return 0;
}