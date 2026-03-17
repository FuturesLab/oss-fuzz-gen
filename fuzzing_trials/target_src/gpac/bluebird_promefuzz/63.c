#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Step 1: Prepare environment
    GF_ISOFile *isom_file = NULL;
    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 1;
    u32 outOriginalFormat = 0;
    u32 outSchemeType = 0;
    u32 outSchemeVersion = 0;
    const char *outSchemeURI = NULL;
    const char *outKMS_URI = NULL;
    Bool outSelectiveEncryption = 0;
    u32 outIVLength = 0;
    u32 outKeyIndicationLength = 0;

    const char *sdp = NULL;
    u32 length = 0;

    const char *xmlnamespace = NULL;
    const char *schema_loc = NULL;
    const char *content_encoding = NULL;

    // Step 2: Write data to dummy file
    write_dummy_file(Data, Size);

    // Step 3: Invoke target functions
    gf_isom_get_ismacryp_info(isom_file, trackNumber, sampleDescriptionIndex, 
                              &outOriginalFormat, &outSchemeType, &outSchemeVersion, 
                              &outSchemeURI, &outKMS_URI, &outSelectiveEncryption, 
                              &outIVLength, &outKeyIndicationLength);

    gf_isom_sdp_get(isom_file, &sdp, &length);

    gf_isom_set_generic_protection(isom_file, trackNumber, sampleDescriptionIndex, 
                                   outSchemeType, outSchemeVersion, 
                                   (char *)outSchemeURI, (char *)outKMS_URI);

    gf_isom_probe_file("./dummy_file");

    gf_isom_new_external_track(isom_file, 0, 0, outSchemeType, 0, "./dummy_file");

    gf_isom_get_xml_metadata_description(isom_file, trackNumber, sampleDescriptionIndex, 
                                         &xmlnamespace, &schema_loc, &content_encoding);

    // Step 4: Cleanup
    // Assuming there are cleanup functions to close or free the ISO file and other resources.
    // For example: gf_isom_close(isom_file);

    return 0;
}