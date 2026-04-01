// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_write_callback at isom_intern.c:1104:8 in isomedia.h
// gf_isom_hint_max_chunk_duration at isom_write.c:5913:8 in isomedia.h
// gf_isom_remove_track_from_root_od at isom_write.c:179:8 in isomedia.h
// gf_isom_remove_cenc_senc_box at drm_sample.c:996:8 in isomedia.h
// gf_isom_set_timescale at isom_write.c:451:8 in isomedia.h
// gf_isom_remove_chapter at isom_write.c:3300:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_Err dummy_on_block_out(void *usr_data, u8 *block, u32 block_size, void *cbk_data, u32 cbk_magic) {
    return GF_OK;
}

static GF_Err dummy_on_block_patch(void *usr_data, u8 *block, u32 block_size, u64 block_offset, Bool is_insert) {
    return GF_OK;
}

static void dummy_on_last_block_start(void *usr_data) {
}

int LLVMFuzzerTestOneInput_268(const uint8_t *Data, size_t Size) {
    // Create a dummy file to ensure the function behaves as expected
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) return 0;
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    // Fuzz gf_isom_set_write_callback
    gf_isom_set_write_callback(isom_file, dummy_on_block_out, dummy_on_block_patch, dummy_on_last_block_start, NULL, 1024);

    // Fuzz gf_isom_hint_max_chunk_duration
    if (Size >= 8) {
        u32 trackNumber = *((u32 *)(Data));
        u32 maxChunkDur = *((u32 *)(Data + 4));
        gf_isom_hint_max_chunk_duration(isom_file, trackNumber, maxChunkDur);
    }

    // Fuzz gf_isom_remove_track_from_root_od
    if (Size >= 4) {
        u32 trackNumber = *((u32 *)(Data));
        gf_isom_remove_track_from_root_od(isom_file, trackNumber);
    }

    // Fuzz gf_isom_remove_cenc_senc_box
    if (Size >= 4) {
        u32 trackNumber = *((u32 *)(Data));
        gf_isom_remove_cenc_senc_box(isom_file, trackNumber);
    }

    // Fuzz gf_isom_set_timescale
    if (Size >= 4) {
        u32 timeScale = *((u32 *)(Data));
        gf_isom_set_timescale(isom_file, timeScale);
    }

    // Fuzz gf_isom_remove_chapter
    if (Size >= 8) {
        u32 trackNumber = *((u32 *)(Data));
        u32 index = *((u32 *)(Data + 4));
        gf_isom_remove_chapter(isom_file, trackNumber, index);
    }

    gf_isom_close(isom_file);
    return 0;
}