#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);

    if (!isom_file) return 0;

    // Prepare dummy variables for function calls
    const char *outURL = NULL;
    const char *outURN = NULL;
    const char *sdp = NULL;
    u32 sdp_length = 0;
    u32 outDescriptionIndex = 0;
    u32 outOriginalFormat = 0;
    u32 outSchemeType = 0;
    u32 outSchemeVersion = 0;
    const char *outMetadata = NULL;

    // Write dummy file if needed
    write_dummy_file(Data, Size);

    // Call gf_isom_get_data_reference
    gf_isom_get_data_reference(isom_file, 1, 1, &outURL, &outURN);

    // Call gf_isom_sdp_get
    gf_isom_sdp_get(isom_file, &sdp, &sdp_length);

    // Call gf_isom_set_generic_protection
    gf_isom_set_generic_protection(isom_file, 1, 1, 0, 1, NULL, NULL);

    // Call gf_isom_set_adobe_protection
    gf_isom_set_adobe_protection(isom_file, 1, 1, 0, 1, 0, NULL, 0);

    // Call gf_isom_clone_sample_description
    gf_isom_clone_sample_description(isom_file, 1, isom_file, 1, 1, NULL, NULL, &outDescriptionIndex);

    // Call gf_isom_get_adobe_protection_info
    gf_isom_get_adobe_protection_info(isom_file, 1, 1, &outOriginalFormat, &outSchemeType, &outSchemeVersion, &outMetadata);

    // Clean up
    gf_isom_close(isom_file);
    return 0;
}