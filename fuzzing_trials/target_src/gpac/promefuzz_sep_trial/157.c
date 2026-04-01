// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_track_interleaving_group at isom_write.c:5868:8 in isomedia.h
// gf_isom_remove_edits at isom_write.c:2797:8 in isomedia.h
// gf_isom_remove_track at isom_write.c:2942:8 in isomedia.h
// gf_isom_set_sample_padding at isom_read.c:2492:8 in isomedia.h
// gf_isom_set_alternate_group_id at isom_write.c:6862:8 in isomedia.h
// gf_isom_set_track_priority_in_group at isom_write.c:5884:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    // Create a dummy ISO file for testing purposes
    GF_ISOFile* isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void cleanup_isofile(GF_ISOFile* isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_157(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile* isom_file = create_dummy_isofile();
    if (!isom_file) return 0;

    u32 trackNumber = *(u32*)Data;
    u32 GroupID = *(u32*)(Data + sizeof(u32));
    u32 padding_bytes = *(u32*)(Data + sizeof(u32) * 2);

    // Fuzz gf_isom_set_track_interleaving_group
    gf_isom_set_track_interleaving_group(isom_file, trackNumber, GroupID);

    // Fuzz gf_isom_remove_edits
    gf_isom_remove_edits(isom_file, trackNumber);

    // Fuzz gf_isom_remove_track
    gf_isom_remove_track(isom_file, trackNumber);

    // Fuzz gf_isom_set_sample_padding
    gf_isom_set_sample_padding(isom_file, trackNumber, padding_bytes);

    // Fuzz gf_isom_set_alternate_group_id
    gf_isom_set_alternate_group_id(isom_file, trackNumber, GroupID);

    // Fuzz gf_isom_set_track_priority_in_group
    gf_isom_set_track_priority_in_group(isom_file, trackNumber, GroupID);

    cleanup_isofile(isom_file);
    return 0;
}