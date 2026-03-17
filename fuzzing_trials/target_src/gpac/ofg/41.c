#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0; // Exit if file creation fails
    }

    u32 trackNumber = 1; // Example track number
    u32 desc_index = 1;  // Example descriptor index
    u32 scheme_type = 0x63656E63; // 'cenc' in hex
    u32 scheme_version = 1; // Example scheme version
    Bool is_selective_enc = GF_TRUE; // Example boolean value

    // Ensure metadata is not NULL and has a valid length
    char *metadata = (char *)malloc(size + 1);
    if (!metadata) {
        gf_isom_close(the_file);
        return 0; // Exit if memory allocation fails
    }
    memcpy(metadata, data, size);
    metadata[size] = '\0'; // Null-terminate the metadata

    u32 len = size;

    // Call the function-under-test
    gf_isom_set_adobe_protection(the_file, trackNumber, desc_index, scheme_type, scheme_version, is_selective_enc, metadata, len);

    // Clean up
    free(metadata);
    gf_isom_close(the_file);

    return 0;
}