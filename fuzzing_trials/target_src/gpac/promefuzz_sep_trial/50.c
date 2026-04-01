// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_sample_from_dts at isom_read.c:2168:5 in isomedia.h
// gf_isom_get_track_duration_orig at isom_read.c:1092:5 in isomedia.h
// gf_isom_get_current_tfdt at isom_read.c:5822:5 in isomedia.h
// gf_isom_get_smooth_next_tfdt at isom_read.c:5835:5 in isomedia.h
// gf_isom_get_track_magic at isom_read.c:6160:5 in isomedia.h
// gf_isom_get_media_duration at isom_read.c:1426:5 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_iso_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        const char dummy_data[4] = {0x00, 0x00, 0x00, 0x00};
        fwrite(dummy_data, sizeof(dummy_data), 1, file);
        fclose(file);
    }
}

static GF_ISOFile* open_dummy_iso_file() {
    // Use a mock function to simulate opening an ISO file
    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) + sizeof(u64)) return 0;

    write_dummy_iso_file();
    GF_ISOFile *isom_file = open_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u64 dts = *(u64 *)(Data + sizeof(u32));

    // Test gf_isom_get_sample_from_dts
    u32 sample_number = gf_isom_get_sample_from_dts(isom_file, trackNumber, dts);

    // Test gf_isom_get_track_duration_orig
    u64 track_duration = gf_isom_get_track_duration_orig(isom_file, trackNumber);

    // Test gf_isom_get_current_tfdt
    u64 current_tfdt = gf_isom_get_current_tfdt(isom_file, trackNumber);

    // Test gf_isom_get_smooth_next_tfdt
    u64 smooth_next_tfdt = gf_isom_get_smooth_next_tfdt(isom_file, trackNumber);

    // Test gf_isom_get_track_magic
    u64 track_magic = gf_isom_get_track_magic(isom_file, trackNumber);

    // Test gf_isom_get_media_duration
    u64 media_duration = gf_isom_get_media_duration(isom_file, trackNumber);

    // Cleanup
    gf_isom_close(isom_file);

    return 0;
}