// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_sample_references at isom_read.c:6727:8 in isomedia.h
// gf_isom_remove_cenc_senc_box at drm_sample.c:996:8 in isomedia.h
// gf_isom_set_track_id at isom_write.c:5076:8 in isomedia.h
// gf_isom_remove_track_references at isom_write.c:5036:8 in isomedia.h
// gf_isom_rtp_set_timescale at hint_track.c:226:8 in isomedia.h
// gf_isom_update_edit_list_duration at isom_write.c:8354:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy ISO file using the API function
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return NULL;
    
    return isom_file;
}

static void free_dummy_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_117(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5) return 0;

    // Create a dummy ISO file
    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Extract parameters
    u32 trackNumber = *((u32 *)Data);
    u32 sampleNumber = *((u32 *)(Data + sizeof(u32)));
    u32 newTrackID = *((u32 *)(Data + sizeof(u32) * 2));
    u32 hintDescriptionIndex = *((u32 *)(Data + sizeof(u32) * 3));
    u32 timeScale = *((u32 *)(Data + sizeof(u32) * 4));

    // Variables for gf_isom_get_sample_references
    u32 refID;
    u32 nb_refs;
    const u32 *refs;

    // Test gf_isom_get_sample_references
    gf_isom_get_sample_references(iso_file, trackNumber, sampleNumber, &refID, &nb_refs, &refs);

    // Test gf_isom_remove_cenc_senc_box
    gf_isom_remove_cenc_senc_box(iso_file, trackNumber);

    // Test gf_isom_set_track_id
    gf_isom_set_track_id(iso_file, trackNumber, newTrackID);

    // Test gf_isom_remove_track_references
    gf_isom_remove_track_references(iso_file, trackNumber);

    // Test gf_isom_rtp_set_timescale
    gf_isom_rtp_set_timescale(iso_file, trackNumber, hintDescriptionIndex, timeScale);

    // Test gf_isom_update_edit_list_duration
    gf_isom_update_edit_list_duration(iso_file, trackNumber);

    // Free the dummy ISO file
    free_dummy_iso_file(iso_file);

    return 0;
}