#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL); // Create a dummy ISO file
    if (the_file == NULL) {
        return 0; // Exit if the file creation fails
    }

    u32 trackNumber = 1; // Set a valid track number
    u32 desc_index = 1; // Set a valid descriptor index
    u32 scheme_type = 0x63656E63; // Example scheme type ('cenc')
    u32 scheme_version = 1; // Example scheme version
    Bool is_selective_enc = GF_TRUE; // Set selective encryption to true

    // Allocate memory for metadata and ensure it is not NULL
    char *metadata = (char *)malloc(size + 1);
    if (metadata == NULL) {
        gf_isom_close(the_file);
        return 0;
    }

    // Copy data into metadata and ensure it's null-terminated
    memcpy(metadata, data, size);
    metadata[size] = '\0';

    u32 len = size; // Set the length of the metadata

    // Call the function-under-test
    gf_isom_set_adobe_protection(the_file, trackNumber, desc_index, scheme_type, scheme_version, is_selective_enc, metadata, len);

    // Clean up resources
    free(metadata);
    gf_isom_close(the_file);

    return 0;
}