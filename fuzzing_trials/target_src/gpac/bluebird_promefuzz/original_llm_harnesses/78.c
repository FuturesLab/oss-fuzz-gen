// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_track_flags at isom_write.c:277:8 in isomedia.h
// gf_isom_remove_track_references at isom_write.c:5036:8 in isomedia.h
// gf_isom_3gp_config_update at sample_descs.c:660:8 in isomedia.h
// gf_isom_rtp_set_timescale at hint_track.c:226:8 in isomedia.h
// gf_isom_set_media_timescale at isom_write.c:5276:8 in isomedia.h
// gf_isom_set_forced_text at tx3g.c:973:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return file;
}

static void cleanup_isofile(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) return 0;

    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return 0;

    u32 trackNumber = *((u32*)Data);
    u32 flags = *((u32*)(Data + sizeof(u32)));
    GF_ISOMTrackFlagOp op = (GF_ISOMTrackFlagOp)(*(Data + 2 * sizeof(u32)));
    u32 new_timescale = *((u32*)(Data + 3 * sizeof(u32)));

    // Fuzz gf_isom_set_track_flags
    gf_isom_set_track_flags(isom_file, trackNumber, flags, op);

    // Fuzz gf_isom_remove_track_references
    gf_isom_remove_track_references(isom_file, trackNumber);

    // Fuzz gf_isom_3gp_config_update
    GF_3GPConfig config;
    gf_isom_3gp_config_update(isom_file, trackNumber, &config, flags);

    // Fuzz gf_isom_rtp_set_timescale
    gf_isom_rtp_set_timescale(isom_file, trackNumber, flags, new_timescale);

    // Fuzz gf_isom_set_media_timescale
    gf_isom_set_media_timescale(isom_file, trackNumber, new_timescale, flags, op);

    // Fuzz gf_isom_set_forced_text
    gf_isom_set_forced_text(isom_file, trackNumber, flags, op);

    cleanup_isofile(isom_file);
    return 0;
}