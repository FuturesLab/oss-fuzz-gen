#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy ISO file structure
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = Data[0];
    const char *xmlnamespace = (Size > 1) ? (const char *)&Data[1] : NULL;
    const char *schema_loc = (Size > 2) ? (const char *)&Data[2] : NULL;
    const char *content_encoding = (Size > 3) ? (const char *)&Data[3] : NULL;
    u32 outDescriptionIndex = 0;

    gf_isom_new_xml_metadata_description(iso_file, trackNumber, xmlnamespace, schema_loc, content_encoding, &outDescriptionIndex);

    GF_3GPConfig *config = (GF_3GPConfig *)malloc(sizeof(GF_3GPConfig));
    if (config) {
        gf_isom_3gp_config_new(iso_file, trackNumber, config, xmlnamespace, schema_loc, &outDescriptionIndex);
        free(config);
    }

    u32 format_info = (Size > 4) ? Data[4] : 0;
    u32 peak_data_rate = (Size > 5) ? Data[5] : 0;

    gf_isom_truehd_config_new(iso_file, trackNumber, (char *)xmlnamespace, (char *)schema_loc, format_info, peak_data_rate, &outDescriptionIndex);

    gf_isom_new_xml_subtitle_description(iso_file, trackNumber, xmlnamespace, schema_loc, content_encoding, &outDescriptionIndex);

    GF_ISOFile *orig_file = create_dummy_iso_file();
    if (orig_file) {
        gf_isom_clone_sample_description(iso_file, trackNumber, orig_file, trackNumber, outDescriptionIndex, xmlnamespace, schema_loc, &outDescriptionIndex);
        cleanup_iso_file(orig_file);
    }

    const char *mimes = NULL;
    gf_isom_xml_subtitle_get_description(iso_file, trackNumber, outDescriptionIndex, &xmlnamespace, &schema_loc, &mimes);

    cleanup_iso_file(iso_file);
    return 0;
}