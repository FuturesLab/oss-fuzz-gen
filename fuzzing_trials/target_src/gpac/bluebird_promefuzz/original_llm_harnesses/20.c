// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_evte_config_new at sample_descs.c:1846:8 in isomedia.h
// gf_isom_remove_sample_group at isom_write.c:7632:8 in isomedia.h
// gf_isom_set_ctts_v1 at isom_write.c:7867:8 in isomedia.h
// gf_isom_remove_cenc_senc_box at drm_sample.c:996:8 in isomedia.h
// gf_isom_set_media_subtype at isom_write.c:6197:8 in isomedia.h
// gf_isom_remove_stream_description at isom_write.c:909:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static GF_ISOFile* create_dummy_isofile() {
    // Assuming a temporary directory is needed
    GF_ISOFile *iso_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static void cleanup_dummy_isofile(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    // Prepare dummy file
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    GF_ISOFile *iso_file = create_dummy_isofile();
    if (!iso_file) return 0;

    u32 trackNumber = 1;
    u32 outDescriptionIndex = 0;
    u32 grouping_type = 0x676E726C; // 'gnrl'
    u32 ctts_shift = 0;
    u32 sampleDescriptionIndex = 0;
    u32 new_type = 0x6D703476; // 'mp4v'

    // Fuzz gf_isom_evte_config_new
    gf_isom_evte_config_new(iso_file, trackNumber, &outDescriptionIndex);

    // Fuzz gf_isom_remove_sample_group
    gf_isom_remove_sample_group(iso_file, trackNumber, grouping_type);

    // Fuzz gf_isom_set_ctts_v1
    gf_isom_set_ctts_v1(iso_file, trackNumber, ctts_shift);

    // Fuzz gf_isom_remove_cenc_senc_box
    gf_isom_remove_cenc_senc_box(iso_file, trackNumber);

    // Fuzz gf_isom_set_media_subtype
    gf_isom_set_media_subtype(iso_file, trackNumber, sampleDescriptionIndex, new_type);

    // Fuzz gf_isom_remove_stream_description
    gf_isom_remove_stream_description(iso_file, trackNumber, sampleDescriptionIndex);

    cleanup_dummy_isofile(iso_file);

    return 0;
}