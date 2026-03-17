#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
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

int LLVMFuzzerTestOneInput_147(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 2) return 0;

    // Initialize variables
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    const char *outURL = NULL;
    const char *outURN = NULL;
    GF_Err err;

    // Invoke gf_isom_get_data_reference
    err = gf_isom_get_data_reference(isom_file, trackNumber, sampleDescriptionIndex, &outURL, &outURN);
    if (err != GF_OK) goto cleanup;

    // Prepare AVS3 config
    GF_AVS3VConfig avs3_cfg;
    memset(&avs3_cfg, 0, sizeof(GF_AVS3VConfig));
    u32 outDescriptionIndex;

    // Invoke gf_isom_avs3v_config_new
    err = gf_isom_avs3v_config_new(isom_file, trackNumber, &avs3_cfg, outURL, outURN, &outDescriptionIndex);
    if (err != GF_OK) goto cleanup;

    // Prepare parameters for gf_isom_new_stxt_description
    const char *mime = "text/plain";
    const char *encoding = "UTF-8";
    const char *config = "sample config";

    // Invoke gf_isom_new_stxt_description
    err = gf_isom_new_stxt_description(isom_file, trackNumber, 'stxt', mime, encoding, config, &outDescriptionIndex);
    if (err != GF_OK) goto cleanup;

    // Prepare parameters for gf_isom_truehd_config_new
    u32 format_info = 0;
    u32 peak_data_rate = 0;

    // Invoke gf_isom_truehd_config_new
    err = gf_isom_truehd_config_new(isom_file, trackNumber, NULL, NULL, format_info, peak_data_rate, &outDescriptionIndex);
    if (err != GF_OK) goto cleanup;

    // Prepare AVC config
    GF_AVCConfig avc_cfg;
    memset(&avc_cfg, 0, sizeof(GF_AVCConfig));

    // Invoke gf_isom_avc_config_new
    err = gf_isom_avc_config_new(isom_file, trackNumber, &avc_cfg, NULL, NULL, &outDescriptionIndex);
    if (err != GF_OK) goto cleanup;

    // Prepare parameters for gf_isom_xml_subtitle_get_description
    const char *xmlnamespace = NULL;
    const char *xml_schema_loc = NULL;
    const char *mimes = NULL;

    // Invoke gf_isom_xml_subtitle_get_description
    err = gf_isom_xml_subtitle_get_description(isom_file, trackNumber, sampleDescriptionIndex, &xmlnamespace, &xml_schema_loc, &mimes);
    if (err != GF_OK) goto cleanup;

cleanup:
    // Cleanup
    gf_isom_close(isom_file);
    return 0;
}