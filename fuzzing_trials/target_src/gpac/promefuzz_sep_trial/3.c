// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_chunks_infos at isom_read.c:2906:8 in isomedia.h
// gf_isom_set_media_type at isom_write.c:6188:8 in isomedia.h
// gf_isom_purge_track_reference at isom_write.c:4999:8 in isomedia.h
// gf_isom_remove_cenc_seig_sample_group at drm_sample.c:1037:8 in isomedia.h
// gf_isom_remove_track_references at isom_write.c:5036:8 in isomedia.h
// gf_isom_purge_samples at isom_read.c:3192:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

// Dummy implementation of gf_isom_open_file and gf_isom_close_file
// Since we don't have the full definition of GF_ISOFile, we can't allocate it directly
static GF_ISOFile* gf_isom_open_file(const char *filename, GF_ISOOpenMode mode) {
    // Normally, you would have actual logic to open and return a GF_ISOFile object
    return NULL;
}

static void gf_isom_close_file(GF_ISOFile *iso_file) {
    // Normally, you would have actual logic to close and clean up a GF_ISOFile object
}

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there is enough data for a u32 track number

    GF_ISOFile *iso_file = gf_isom_open_file("./dummy_file", GF_ISOM_OPEN_READ);
    if (!iso_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    const uint8_t *remainingData = Data + 4;
    size_t remainingSize = Size - 4;

    // Fuzz gf_isom_get_chunks_infos
    u32 dur_min, dur_avg, dur_max, size_min, size_avg, size_max;
    gf_isom_get_chunks_infos(iso_file, trackNumber, &dur_min, &dur_avg, &dur_max, &size_min, &size_avg, &size_max);

    // Fuzz gf_isom_set_media_type
    if (remainingSize >= 4) {
        u32 new_type = *(u32 *)remainingData;
        gf_isom_set_media_type(iso_file, trackNumber, new_type);
        remainingData += 4;
        remainingSize -= 4;
    }

    // Fuzz gf_isom_purge_track_reference
    gf_isom_purge_track_reference(iso_file, trackNumber);

    // Fuzz gf_isom_remove_cenc_seig_sample_group
    gf_isom_remove_cenc_seig_sample_group(iso_file, trackNumber);

    // Fuzz gf_isom_remove_track_references
    gf_isom_remove_track_references(iso_file, trackNumber);

    // Fuzz gf_isom_purge_samples
    if (remainingSize >= 4) {
        u32 nb_samples = *(u32 *)remainingData;
        gf_isom_purge_samples(iso_file, trackNumber, nb_samples);
    }

    gf_isom_close_file(iso_file);
    return 0;
}