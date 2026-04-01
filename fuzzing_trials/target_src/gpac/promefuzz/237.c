// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_timescale at isom_write.c:451:8 in isomedia.h
// gf_isom_sdp_clean_track at hint_track.c:790:8 in isomedia.h
// gf_isom_rewrite_track_dependencies at isom_write.c:5120:8 in isomedia.h
// gf_isom_set_media_timescale at isom_write.c:5276:8 in isomedia.h
// gf_isom_remove_edits at isom_write.c:2797:8 in isomedia.h
// gf_isom_text_set_display_flags at isom_write.c:8293:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile *initialize_iso_file() {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return NULL;

    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_237(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    GF_ISOFile *isom_file = initialize_iso_file();
    if (!isom_file) return 0;

    u32 param1 = *((u32 *)Data);
    u32 param2 = Size > 8 ? *((u32 *)(Data + 4)) : 0;
    u32 param3 = Size > 12 ? *((u32 *)(Data + 8)) : 0;
    u32 param4 = Size > 16 ? *((u32 *)(Data + 12)) : 0;
    u32 param5 = Size > 20 ? *((u32 *)(Data + 16)) : 0;

    gf_isom_set_timescale(isom_file, param1);
    gf_isom_sdp_clean_track(isom_file, param1);
    gf_isom_rewrite_track_dependencies(isom_file, param1);
    gf_isom_set_media_timescale(isom_file, param1, param2, param3, param4);
    gf_isom_remove_edits(isom_file, param1);
    gf_isom_text_set_display_flags(isom_file, param1, param2, param3, param4);

    cleanup_iso_file(isom_file);
    return 0;
}