// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_interleave_time at isom_write.c:3431:8 in isomedia.h
// gf_isom_set_nalu_extract_mode at isom_read.c:5481:8 in isomedia.h
// gf_isom_remove_edit at isom_write.c:2825:8 in isomedia.h
// gf_isom_get_track_switch_group_count at isom_read.c:4813:8 in isomedia.h
// gf_isom_hint_max_chunk_size at isom_write.c:5898:8 in isomedia.h
// gf_isom_truehd_config_get at sample_descs.c:416:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    GF_ISOFile* iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!iso_file) return NULL;

    return iso_file;
}

static void cleanup_dummy_iso_file(GF_ISOFile* iso_file) {
    if (!iso_file) return;
    gf_isom_close(iso_file);
}

int LLVMFuzzerTestOneInput_216(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile* iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 interleave_time = *(u32*)Data;
    gf_isom_set_interleave_time(iso_file, interleave_time);

    if (Size < 2 * sizeof(u32)) {
        cleanup_dummy_iso_file(iso_file);
        return 0;
    }

    u32 track_number = *(u32*)(Data + sizeof(u32));

    if (Size < 3 * sizeof(u32)) {
        cleanup_dummy_iso_file(iso_file);
        return 0;
    }

    GF_ISONaluExtractMode nalu_mode = (GF_ISONaluExtractMode)*(u32*)(Data + 2 * sizeof(u32));
    gf_isom_set_nalu_extract_mode(iso_file, track_number, nalu_mode);

    if (Size < 4 * sizeof(u32)) {
        cleanup_dummy_iso_file(iso_file);
        return 0;
    }

    u32 edit_index = *(u32*)(Data + 3 * sizeof(u32));
    gf_isom_remove_edit(iso_file, track_number, edit_index);

    u32 alternate_group_id = 0;
    u32 nb_groups = 0;
    gf_isom_get_track_switch_group_count(iso_file, track_number, &alternate_group_id, &nb_groups);

    if (Size < 5 * sizeof(u32)) {
        cleanup_dummy_iso_file(iso_file);
        return 0;
    }

    u32 max_chunk_size = *(u32*)(Data + 4 * sizeof(u32));
    gf_isom_hint_max_chunk_size(iso_file, track_number, max_chunk_size);

    if (Size < 6 * sizeof(u32)) {
        cleanup_dummy_iso_file(iso_file);
        return 0;
    }

    u32 sample_description_index = *(u32*)(Data + 5 * sizeof(u32));
    u32 format_info = 0;
    u32 peak_data_rate = 0;
    gf_isom_truehd_config_get(iso_file, track_number, sample_description_index, &format_info, &peak_data_rate);

    cleanup_dummy_iso_file(iso_file);
    return 0;
}