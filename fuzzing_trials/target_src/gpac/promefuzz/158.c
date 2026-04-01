// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_opus_config_get_desc at sample_descs.c:557:8 in isomedia.h
// gf_isom_set_mpegh_compatible_profiles at isom_write.c:9336:8 in isomedia.h
// gf_isom_change_mpeg4_description at isom_write.c:1732:8 in isomedia.h
// gf_isom_copy_sample_info at isom_write.c:8078:8 in isomedia.h
// gf_isom_get_pixel_aspect_ratio at isom_read.c:3946:8 in isomedia.h
// gf_isom_get_cenc_info at drm_sample.c:726:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_158(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    if (Size < sizeof(u32) * 3) {
        gf_isom_close(isom_file);
        return 0;
    }

    u32 trackNumber = ((u32 *)Data)[0];
    u32 sampleDescriptionIndex = ((u32 *)Data)[1];
    u32 sampleNumber = ((u32 *)Data)[2];
    const u32 *profiles = (Size > sizeof(u32) * 3) ? (const u32 *)(Data + sizeof(u32) * 3) : NULL;
    u32 nb_compatible_profiles = (Size - sizeof(u32) * 3) / sizeof(u32);

    GF_OpusConfig opcfg;
    GF_ESD newESD;
    u32 hSpacing, vSpacing;
    u32 outOriginalFormat, outSchemeType, outSchemeVersion;

    // Fuzz gf_isom_opus_config_get_desc
    gf_isom_opus_config_get_desc(isom_file, trackNumber, sampleDescriptionIndex, &opcfg);

    // Fuzz gf_isom_set_mpegh_compatible_profiles
    gf_isom_set_mpegh_compatible_profiles(isom_file, trackNumber, sampleDescriptionIndex, profiles, nb_compatible_profiles);

    // Fuzz gf_isom_change_mpeg4_description
    gf_isom_change_mpeg4_description(isom_file, trackNumber, sampleDescriptionIndex, &newESD);

    // Fuzz gf_isom_copy_sample_info
    gf_isom_copy_sample_info(isom_file, trackNumber, isom_file, trackNumber, sampleNumber);

    // Fuzz gf_isom_get_pixel_aspect_ratio
    gf_isom_get_pixel_aspect_ratio(isom_file, trackNumber, sampleDescriptionIndex, &hSpacing, &vSpacing);

    // Fuzz gf_isom_get_cenc_info
    gf_isom_get_cenc_info(isom_file, trackNumber, sampleDescriptionIndex, &outOriginalFormat, &outSchemeType, &outSchemeVersion);

    gf_isom_close(isom_file);
    return 0;
}