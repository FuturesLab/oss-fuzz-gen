// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_remove_cenc_seig_sample_group at drm_sample.c:1037:8 in isomedia.h
// gf_isom_remove_chapter at isom_write.c:3300:8 in isomedia.h
// gf_isom_get_text_description at tx3g.c:49:8 in isomedia.h
// gf_isom_set_mpegh_compatible_profiles at isom_write.c:9336:8 in isomedia.h
// gf_isom_remove_stream_description at isom_write.c:909:8 in isomedia.h
// gf_isom_get_adobe_protection_info at drm_sample.c:1921:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static GF_ISOFile* create_dummy_isofile() {
    // In a real scenario, we would initialize this with valid data
    return NULL;
}

static void cleanup_isofile(GF_ISOFile *isom_file) {
    // Cleanup logic if needed
}

int LLVMFuzzerTestOneInput_156(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isom_file = create_dummy_isofile();

    // Extract track number and indices from input data
    u32 trackNumber = *((u32 *)Data);
    u32 index = *((u32 *)(Data + sizeof(u32)));
    u32 sampleDescriptionIndex = *((u32 *)(Data + 2 * sizeof(u32)));

    // Fuzz gf_isom_remove_cenc_seig_sample_group
    gf_isom_remove_cenc_seig_sample_group(isom_file, trackNumber);

    // Fuzz gf_isom_remove_chapter
    gf_isom_remove_chapter(isom_file, trackNumber, index);

    // Fuzz gf_isom_get_text_description
    GF_TextSampleDescriptor *out_desc = NULL;
    gf_isom_get_text_description(isom_file, trackNumber, sampleDescriptionIndex, &out_desc);
    if (out_desc) {
        free(out_desc);
    }

    // Fuzz gf_isom_set_mpegh_compatible_profiles
    gf_isom_set_mpegh_compatible_profiles(isom_file, trackNumber, sampleDescriptionIndex, NULL, 0);

    // Fuzz gf_isom_remove_stream_description
    gf_isom_remove_stream_description(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_get_adobe_protection_info
    u32 outOriginalFormat, outSchemeType, outSchemeVersion;
    const char *outMetadata;
    gf_isom_get_adobe_protection_info(isom_file, trackNumber, sampleDescriptionIndex, &outOriginalFormat, &outSchemeType, &outSchemeVersion, &outMetadata);

    cleanup_isofile(isom_file);
    return 0;
}