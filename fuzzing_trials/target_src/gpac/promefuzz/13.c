// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_sample_count at isom_read.c:1767:5 in isomedia.h
// gf_isom_get_track_id at isom_read.c:796:15 in isomedia.h
// gf_isom_find_od_id_for_track at media_odf.c:511:5 in isomedia.h
// gf_isom_get_media_type at isom_read.c:1586:5 in isomedia.h
// gf_isom_get_sample_duration at isom_read.c:1990:5 in isomedia.h
// gf_isom_get_track_count at isom_read.c:783:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file(const uint8_t *Data, size_t Size) {
    // Simulate opening an ISO file, as the actual structure is opaque
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!iso_file) return NULL;

    // Simulate writing data to "./dummy_file"
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file(Data, Size);
    if (!iso_file) return 0;

    u32 trackNumber = *(u32*)Data;
    u32 sampleNumber = (Size > sizeof(u32)) ? *(u32*)(Data + sizeof(u32)) : 0;

    // Fuzz gf_isom_get_sample_count
    u32 sample_count = gf_isom_get_sample_count(iso_file, trackNumber);

    // Fuzz gf_isom_get_track_id
    GF_ISOTrackID track_id = gf_isom_get_track_id(iso_file, trackNumber);

    // Fuzz gf_isom_find_od_id_for_track
    u32 od_id = gf_isom_find_od_id_for_track(iso_file, trackNumber);

    // Fuzz gf_isom_get_media_type
    u32 media_type = gf_isom_get_media_type(iso_file, trackNumber);

    // Fuzz gf_isom_get_sample_duration
    u32 sample_duration = gf_isom_get_sample_duration(iso_file, trackNumber, sampleNumber);

    // Fuzz gf_isom_get_track_count
    u32 track_count = gf_isom_get_track_count(iso_file);

    // Cleanup
    cleanup_iso_file(iso_file);

    return 0;
}