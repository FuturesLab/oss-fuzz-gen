// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_default_sync_track at isom_read.c:4209:6 in isomedia.h
// gf_isom_get_track_id at isom_read.c:796:15 in isomedia.h
// gf_isom_get_avg_sample_size at isom_read.c:2030:5 in isomedia.h
// gf_isom_get_highest_track_in_scalable_segment at isom_read.c:3640:15 in isomedia.h
// gf_isom_get_mastering_display_colour_info at isom_read.c:6475:44 in isomedia.h
// gf_isom_get_last_created_track_id at isom_write.c:596:15 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_124(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure enough data for a u32 track number

    // Create a dummy GF_ISOFile pointer
    GF_ISOFile *isom = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom) {
        return 0;
    }

    // Write the data to a dummy file
    write_dummy_file(Data, Size);

    u32 trackNumber = *(u32 *)Data;
    Data += 4;
    Size -= 4;

    // Fuzz gf_isom_set_default_sync_track
    gf_isom_set_default_sync_track(isom, trackNumber);

    // Fuzz gf_isom_get_track_id
    GF_ISOTrackID trackID = gf_isom_get_track_id(isom, trackNumber);

    // Fuzz gf_isom_get_avg_sample_size
    u32 avgSampleSize = gf_isom_get_avg_sample_size(isom, trackNumber);

    // Fuzz gf_isom_get_highest_track_in_scalable_segment
    GF_ISOTrackID highestTrackID = gf_isom_get_highest_track_in_scalable_segment(isom, trackNumber);

    // Fuzz gf_isom_get_mastering_display_colour_info
    const GF_MasteringDisplayColourVolumeInfo *colourInfo = gf_isom_get_mastering_display_colour_info(isom, trackNumber, trackNumber);

    // Fuzz gf_isom_get_last_created_track_id
    GF_ISOTrackID lastCreatedTrackID = gf_isom_get_last_created_track_id(isom);

    // Close the ISO file
    gf_isom_close(isom);

    return 0;
}