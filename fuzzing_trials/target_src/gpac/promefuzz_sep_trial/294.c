// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_opus_config_get_desc at sample_descs.c:557:8 in isomedia.h
// gf_isom_get_chunks_infos at isom_read.c:2906:8 in isomedia.h
// gf_isom_set_cenc_protection at drm_sample.c:758:8 in isomedia.h
// gf_isom_get_pixel_aspect_ratio at isom_read.c:3946:8 in isomedia.h
// gf_isom_get_cenc_info at drm_sample.c:726:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_copy_sample_info at isom_write.c:8078:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
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

int LLVMFuzzerTestOneInput_294(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0; // Ensure enough data for indices and track numbers

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    // Prepare data for function calls
    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    u32 dummyValue = *(u32 *)(Data + 2 * sizeof(u32));

    // Fuzz gf_isom_opus_config_get_desc
    GF_OpusConfig opcfg;
    gf_isom_opus_config_get_desc(isom_file, trackNumber, sampleDescriptionIndex, &opcfg);

    // Fuzz gf_isom_get_chunks_infos
    u32 dur_min, dur_avg, dur_max, size_min, size_avg, size_max;
    gf_isom_get_chunks_infos(isom_file, trackNumber, &dur_min, &dur_avg, &dur_max, &size_min, &size_avg, &size_max);

    // Fuzz gf_isom_set_cenc_protection
    gf_isom_set_cenc_protection(isom_file, trackNumber, sampleDescriptionIndex, dummyValue, dummyValue, dummyValue, dummyValue, dummyValue, (u8 *)Data, Size);

    // Fuzz gf_isom_get_pixel_aspect_ratio
    u32 hSpacing, vSpacing;
    gf_isom_get_pixel_aspect_ratio(isom_file, trackNumber, sampleDescriptionIndex, &hSpacing, &vSpacing);

    // Fuzz gf_isom_get_cenc_info
    u32 outOriginalFormat, outSchemeType, outSchemeVersion;
    gf_isom_get_cenc_info(isom_file, trackNumber, sampleDescriptionIndex, &outOriginalFormat, &outSchemeType, &outSchemeVersion);

    // Fuzz gf_isom_copy_sample_info
    GF_ISOFile *src_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (src_file) {
        gf_isom_copy_sample_info(isom_file, trackNumber, src_file, trackNumber, sampleDescriptionIndex);
        gf_isom_close(src_file);
    }

    gf_isom_close(isom_file);
    return 0;
}