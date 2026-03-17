#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "gpac/isomedia.h" // Include the appropriate header for GF_ISOFile
#include "gpac/internal/isomedia_dev.h" // Include the internal header for proper struct definition

int LLVMFuzzerTestOneInput_267(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract necessary values
    if (size < sizeof(uint32_t) * 4 + 2) {
        return 0;
    }

    // Initialize parameters
    // Provide a temporary directory path for the third argument
    GF_ISOFile *the_file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, "/tmp"); // Use library function to initialize GF_ISOFile
    if (!the_file) {
        return 0;
    }

    uint32_t trackNumber = *(uint32_t *)(data);
    uint32_t desc_index = *(uint32_t *)(data + sizeof(uint32_t));
    uint32_t scheme_type = *(uint32_t *)(data + 2 * sizeof(uint32_t));
    uint32_t scheme_version = *(uint32_t *)(data + 3 * sizeof(uint32_t));

    // Extract strings ensuring null-termination
    size_t uri_offset = 4 * sizeof(uint32_t);
    size_t uri_length = (size - uri_offset) / 2;
    char *scheme_uri = (char *)malloc(uri_length + 1);
    char *kms_URI = (char *)malloc(uri_length + 1);
    if (!scheme_uri || !kms_URI) {
        gf_isom_close(the_file);
        free(scheme_uri);
        free(kms_URI);
        return 0;
    }

    memcpy(scheme_uri, data + uri_offset, uri_length);
    scheme_uri[uri_length] = '\0';

    memcpy(kms_URI, data + uri_offset + uri_length, uri_length);
    kms_URI[uri_length] = '\0';

    // Call the function-under-test
    gf_isom_set_generic_protection(the_file, trackNumber, desc_index, scheme_type, scheme_version, scheme_uri, kms_URI);

    // Clean up
    gf_isom_close(the_file);
    free(scheme_uri);
    free(kms_URI);

    return 0;
}