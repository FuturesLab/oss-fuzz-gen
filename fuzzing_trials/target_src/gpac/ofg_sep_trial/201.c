#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    u32 trackNumber = size > 0 ? data[0] : 1;
    u32 desc_index = size > 1 ? data[1] : 1;
    u32 scheme_type = size > 2 ? data[2] : 1;
    u32 scheme_version = size > 3 ? data[3] : 1;

    // Ensure that scheme_uri and kms_URI are null-terminated strings
    char scheme_uri[256] = "default_scheme_uri";
    char kms_URI[256] = "default_kms_URI";

    if (size > 4) {
        size_t uri_length = size - 4 < 255 ? size - 4 : 255;
        memcpy(scheme_uri, data + 4, uri_length);
        scheme_uri[uri_length] = '\0';
    }

    if (size > 5) {
        size_t uri_length = size - 5 < 255 ? size - 5 : 255;
        memcpy(kms_URI, data + 5, uri_length);
        kms_URI[uri_length] = '\0';
    }

    Bool selective_encryption = size > 6 ? data[6] % 2 : 1;
    u32 KI_length = size > 7 ? data[7] : 8;
    u32 IV_length = size > 8 ? data[8] : 16;

    // Call the function under test
    gf_isom_set_ismacryp_protection(the_file, trackNumber, desc_index, scheme_type,
                                    scheme_version, scheme_uri, kms_URI,
                                    selective_encryption, KI_length, IV_length);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}