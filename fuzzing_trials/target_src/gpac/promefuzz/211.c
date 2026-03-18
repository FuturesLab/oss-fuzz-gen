// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_avc_svc_type at avc_ext.c:2682:16 in isomedia.h
// gf_isom_get_track_by_id at isom_read.c:807:5 in isomedia.h
// gf_isom_get_media_type at isom_read.c:1586:5 in isomedia.h
// gf_isom_get_cenc_info at drm_sample.c:726:8 in isomedia.h
// gf_isom_set_default_sync_track at isom_read.c:4209:6 in isomedia.h
// gf_isom_is_media_encrypted at drm_sample.c:193:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    // For simplicity, we assume GF_ISOFile can be initialized through a function
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!iso_file) return NULL;

    // Write the input data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_211(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0; // Not enough data for trackNumber and sampleDescriptionIndex

    GF_ISOFile *iso_file = initialize_iso_file(Data, Size);
    if (!iso_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    GF_ISOTrackID trackID = *((GF_ISOTrackID *)(Data + 2 * sizeof(u32)));

    // Fuzz gf_isom_get_avc_svc_type
    GF_ISOMAVCType avc_type = gf_isom_get_avc_svc_type(iso_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_get_track_by_id
    u32 track_num = gf_isom_get_track_by_id(iso_file, trackID);

    // Fuzz gf_isom_get_media_type
    u32 media_type = gf_isom_get_media_type(iso_file, trackNumber);

    // Fuzz gf_isom_get_cenc_info
    u32 outOriginalFormat, outSchemeType, outSchemeVersion;
    GF_Err cenc_err = gf_isom_get_cenc_info(iso_file, trackNumber, sampleDescriptionIndex, &outOriginalFormat, &outSchemeType, &outSchemeVersion);

    // Fuzz gf_isom_set_default_sync_track
    gf_isom_set_default_sync_track(iso_file, trackNumber);

    // Fuzz gf_isom_is_media_encrypted
    u32 encryption_scheme = gf_isom_is_media_encrypted(iso_file, trackNumber, sampleDescriptionIndex);

    // Cleanup
    cleanup_iso_file(iso_file);

    return 0;
}