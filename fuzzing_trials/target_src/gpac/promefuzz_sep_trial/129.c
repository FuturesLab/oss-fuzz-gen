// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_has_sample_dependency at isom_read.c:1904:6 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_last_producer_time_box at isom_read.c:5800:6 in isomedia.h
// gf_isom_get_sample_sync at isom_read.c:2080:6 in isomedia.h
// gf_isom_is_track_fragmented at movie_fragments.c:3512:6 in isomedia.h
// gf_isom_is_single_av at isom_read.c:4218:6 in isomedia.h
// gf_isom_is_self_contained at isom_read.c:2158:6 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_129(const uint8_t *Data, size_t Size) {
    if (Size < 3 * sizeof(u32) + 2 * sizeof(u64) + sizeof(Bool)) {
        return 0;
    }

    // Initialize a GF_ISOFile structure
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    // Initialize variables for the first function
    GF_ISOTrackID refTrackID;
    u64 ntp, timestamp;
    Bool reset_info;

    // Extract data for the first function
    if (Size >= sizeof(GF_ISOTrackID) + 2 * sizeof(u64) + sizeof(Bool)) {
        refTrackID = *(GF_ISOTrackID *) Data;
        Data += sizeof(GF_ISOTrackID);
        ntp = *(u64 *) Data;
        Data += sizeof(u64);
        timestamp = *(u64 *) Data;
        Data += sizeof(u64);
        reset_info = *(Bool *) Data;
        Data += sizeof(Bool);
        Size -= sizeof(GF_ISOTrackID) + 2 * sizeof(u64) + sizeof(Bool);

        // Call the first target API function
        gf_isom_get_last_producer_time_box(isom_file, &refTrackID, &ntp, &timestamp, reset_info);
    }

    // Initialize variables for the second function
    u32 trackNumber, sampleNumber;

    // Extract data for the second function
    if (Size >= 2 * sizeof(u32)) {
        trackNumber = *(u32 *) Data;
        Data += sizeof(u32);
        sampleNumber = *(u32 *) Data;
        Data += sizeof(u32);
        Size -= 2 * sizeof(u32);

        // Call the second target API function
        gf_isom_get_sample_sync(isom_file, trackNumber, sampleNumber);
    }

    // Initialize variables for the third function
    GF_ISOTrackID TrackID;

    // Extract data for the third function
    if (Size >= sizeof(GF_ISOTrackID)) {
        TrackID = *(GF_ISOTrackID *) Data;
        Data += sizeof(GF_ISOTrackID);
        Size -= sizeof(GF_ISOTrackID);

        // Call the third target API function
        gf_isom_is_track_fragmented(isom_file, TrackID);
    }

    // Call the fourth target API function
    gf_isom_is_single_av(isom_file);

    // Initialize variables for the fifth function
    u32 sampleDescriptionIndex;

    // Extract data for the fifth function
    if (Size >= sizeof(u32)) {
        trackNumber = *(u32 *) Data;
        Data += sizeof(u32);
        sampleDescriptionIndex = *(u32 *) Data;
        Data += sizeof(u32);
        Size -= 2 * sizeof(u32);

        // Call the fifth target API function
        gf_isom_is_self_contained(isom_file, trackNumber, sampleDescriptionIndex);
    }

    // Extract data for the sixth function
    if (Size >= sizeof(u32)) {
        trackNumber = *(u32 *) Data;
        Data += sizeof(u32);
        Size -= sizeof(u32);

        // Call the sixth target API function
        gf_isom_has_sample_dependency(isom_file, trackNumber);
    }

    // Use a dummy file for any file-related operations
    write_dummy_file(Data, Size);

    // Close the ISO file
    gf_isom_close(isom_file);

    return 0;
}