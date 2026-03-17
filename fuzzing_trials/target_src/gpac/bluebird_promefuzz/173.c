#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile *create_dummy_iso_file() {
    // We cannot know the actual size of GF_ISOFile from the header, so we assume a dummy size
    GF_ISOFile *file = (GF_ISOFile *)malloc(1024);
    if (!file) return NULL;
    memset(file, 0, 1024);
    return file;
}

static void cleanup_iso_file(GF_ISOFile *file) {
    if (file) {
        free(file);
    }
}

int LLVMFuzzerTestOneInput_173(const uint8_t *Data, size_t Size) {
    // Minimum size check to prevent buffer overflow
    if (Size < 4 * sizeof(u64) + sizeof(u32) + sizeof(GF_ISOTrackID) + 1) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Test gf_isom_get_sidx_duration
    u64 sidx_duration;
    u32 sidx_timescale;
    gf_isom_get_sidx_duration(iso_file, &sidx_duration, &sidx_timescale);

    // Test gf_isom_set_removed_bytes
    u64 bytes_removed = *(u64 *)Data;
    gf_isom_set_removed_bytes(iso_file, bytes_removed);

    // Test gf_isom_set_movie_duration
    u64 duration = *(u64 *)(Data + sizeof(u64));
    Bool remove_mehd = Data[sizeof(u64) * 2] % 2;
    gf_isom_set_movie_duration(iso_file, duration, remove_mehd);

    // Test gf_isom_open_progressive_ex
    GF_ISOFile *opened_file = NULL;
    u64 BytesMissing;
    u32 topBoxType;
    gf_isom_open_progressive_ex("./dummy_file", 0, Size, 1, &opened_file, &BytesMissing, &topBoxType);

    // Test gf_isom_set_creation_time
    u64 create_time = *(u64 *)(Data + sizeof(u64) + sizeof(u32));
    u64 modif_time = *(u64 *)(Data + 2 * sizeof(u64) + sizeof(u32));
    gf_isom_set_creation_time(iso_file, create_time, modif_time);

    // Adjusted size check to prevent buffer overflow
    if (Size < 5 * sizeof(u64) + sizeof(u32) + sizeof(GF_ISOTrackID) + 1) {
        cleanup_iso_file(iso_file);
        cleanup_iso_file(opened_file);
        return 0;
    }

    // Test gf_isom_set_fragment_reference_time
    GF_ISOTrackID reference_track_ID = *(GF_ISOTrackID *)(Data + 3 * sizeof(u64) + sizeof(u32));
    u64 ntp = *(u64 *)(Data + 3 * sizeof(u64) + sizeof(u32) + sizeof(GF_ISOTrackID));
    u64 timestamp = *(u64 *)(Data + 4 * sizeof(u64) + sizeof(u32) + sizeof(GF_ISOTrackID));
    Bool at_mux = Data[4 * sizeof(u64) + sizeof(u32) + sizeof(GF_ISOTrackID) * 2] % 2;
    gf_isom_set_fragment_reference_time(iso_file, reference_track_ID, ntp, timestamp, at_mux);

    cleanup_iso_file(iso_file);
    cleanup_iso_file(opened_file);

    return 0;
}