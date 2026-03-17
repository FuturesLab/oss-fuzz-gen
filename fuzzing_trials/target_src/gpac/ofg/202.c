#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_202(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    u32 trackNumber = 1;  // Assuming track number 1 for testing
    u32 desc_index = 1;   // Assuming descriptor index 1 for testing
    u32 scheme_type = 0x63656E63;  // 'cenc' in hex
    u32 scheme_version = 1;  // Version 1 for testing

    char scheme_uri[256];
    char kms_URI[256];

    // Ensure scheme_uri and kms_URI are not NULL
    if (size > 0) {
        size_t uri_size = size < 255 ? size : 255;
        memcpy(scheme_uri, data, uri_size);
        scheme_uri[uri_size] = '\0';
        memcpy(kms_URI, data, uri_size);
        kms_URI[uri_size] = '\0';
    } else {
        strcpy(scheme_uri, "default_scheme_uri");
        strcpy(kms_URI, "default_kms_URI");
    }

    Bool selective_encryption = GF_TRUE;  // Set to true for testing
    u32 KI_length = 16;  // Typical key length
    u32 IV_length = 8;   // Typical IV length

    // Call the function-under-test
    gf_isom_set_ismacryp_protection(the_file, trackNumber, desc_index, scheme_type,
                                    scheme_version, scheme_uri, kms_URI,
                                    selective_encryption, KI_length, IV_length);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}