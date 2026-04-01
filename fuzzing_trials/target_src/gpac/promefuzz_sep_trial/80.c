// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_remove_track_reference at isom_write.c:5051:8 in isomedia.h
// gf_isom_remove_track_from_root_od at isom_write.c:179:8 in isomedia.h
// gf_isom_change_mpeg4_description at isom_write.c:1732:8 in isomedia.h
// gf_isom_set_media_timescale at isom_write.c:5276:8 in isomedia.h
// gf_isom_remove_edits at isom_write.c:2797:8 in isomedia.h
// gf_isom_update_edit_list_duration at isom_write.c:8354:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy ISO file using gf_isom_open
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
}

static GF_ESD* create_dummy_esd() {
    GF_ESD *esd = (GF_ESD *)malloc(sizeof(GF_ESD));
    if (!esd) return NULL;
    memset(esd, 0, sizeof(GF_ESD));
    return esd;
}

int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 ref_type = *(((u32 *)Data) + 1);
    u32 sampleDescriptionIndex = *(((u32 *)Data) + 2);
    u32 new_timescale = *(((u32 *)Data) + 3);
    u32 new_tsinc = (Size > sizeof(u32) * 5) ? *(((u32 *)Data) + 4) : 0;
    u32 force_rescale_type = (Size > sizeof(u32) * 6) ? *(((u32 *)Data) + 5) : 0;

    GF_ESD *newESD = create_dummy_esd();
    if (!newESD) {
        gf_isom_close(iso_file);
        return 0;
    }

    gf_isom_remove_track_reference(iso_file, trackNumber, ref_type);
    gf_isom_remove_track_from_root_od(iso_file, trackNumber);
    gf_isom_change_mpeg4_description(iso_file, trackNumber, sampleDescriptionIndex, newESD);
    gf_isom_set_media_timescale(iso_file, trackNumber, new_timescale, new_tsinc, force_rescale_type);
    gf_isom_remove_edits(iso_file, trackNumber);
    gf_isom_update_edit_list_duration(iso_file, trackNumber);

    free(newESD);
    gf_isom_close(iso_file);

    return 0;
}