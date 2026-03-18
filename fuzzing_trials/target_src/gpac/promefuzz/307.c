// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_evte_config_new at sample_descs.c:1846:8 in isomedia.h
// gf_isom_remove_sample_group at isom_write.c:7632:8 in isomedia.h
// gf_isom_set_sample_group_description at isom_write.c:7626:8 in isomedia.h
// gf_isom_remove_cenc_senc_box at drm_sample.c:996:8 in isomedia.h
// gf_isom_set_track_id at isom_write.c:5076:8 in isomedia.h
// gf_isom_vvc_config_update at avc_ext.c:2433:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

#define DUMMY_FILE "./dummy_file"

static GF_ISOFile* create_dummy_iso_file() {
    // Since GF_ISOFile is an incomplete type, we cannot allocate it directly.
    // We assume there is a function to create or open an ISO file, such as gf_isom_open.
    GF_ISOFile *isom_file = gf_isom_open(DUMMY_FILE, GF_ISOM_OPEN_READ_DUMP, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_307(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 outDescriptionIndex = 0;
    GF_Err result;

    // Fuzz gf_isom_evte_config_new
    result = gf_isom_evte_config_new(isom_file, trackNumber, &outDescriptionIndex);

    // Fuzz gf_isom_remove_sample_group
    if (Size >= 2 * sizeof(u32)) {
        u32 grouping_type = *(u32 *)(Data + sizeof(u32));
        result = gf_isom_remove_sample_group(isom_file, trackNumber, grouping_type);
    }

    // Fuzz gf_isom_set_sample_group_description
    if (Size >= 8 * sizeof(u32)) {
        u32 sampleNumber = *(u32 *)(Data + 2 * sizeof(u32));
        u32 grouping_type = *(u32 *)(Data + 3 * sizeof(u32));
        u32 grouping_type_parameter = *(u32 *)(Data + 4 * sizeof(u32));
        void *data = (void *)(Data + 5 * sizeof(u32));
        u32 data_size = *(u32 *)(Data + 6 * sizeof(u32));
        u32 sgpd_flags = *(u32 *)(Data + 7 * sizeof(u32));
        result = gf_isom_set_sample_group_description(isom_file, trackNumber, sampleNumber, grouping_type, grouping_type_parameter, data, data_size, sgpd_flags);
    }

    // Fuzz gf_isom_remove_cenc_senc_box
    result = gf_isom_remove_cenc_senc_box(isom_file, trackNumber);

    // Fuzz gf_isom_set_track_id
    if (Size >= 2 * sizeof(u32)) {
        GF_ISOTrackID trackID = *(GF_ISOTrackID *)(Data + sizeof(u32));
        result = gf_isom_set_track_id(isom_file, trackNumber, trackID);
    }

    // Fuzz gf_isom_vvc_config_update
    if (Size >= 3 * sizeof(u32) + sizeof(GF_VVCConfig)) {
        u32 sampleDescriptionIndex = *(u32 *)(Data + 2 * sizeof(u32));
        GF_VVCConfig *cfg = (GF_VVCConfig *)(Data + 3 * sizeof(u32));
        result = gf_isom_vvc_config_update(isom_file, trackNumber, sampleDescriptionIndex, cfg);
    }

    cleanup_iso_file(isom_file);
    return 0;
}