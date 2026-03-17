// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_remove_sample at isom_write.c:1541:8 in isomedia.h
// gf_isom_get_track_switch_group_count at isom_read.c:4813:8 in isomedia.h
// gf_isom_set_last_sample_duration at isom_write.c:1419:8 in isomedia.h
// gf_isom_set_ctts_v1 at isom_write.c:7867:8 in isomedia.h
// gf_isom_get_sample_to_group_info at isom_read.c:5214:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 6) return 0;

    // Prepare input data
    u32 trackNumber = *((u32 *)Data);
    u32 sampleNumber = *((u32 *)(Data + sizeof(u32)));
    u32 duration = *((u32 *)(Data + 2 * sizeof(u32)));
    u32 ctts_shift = *((u32 *)(Data + 3 * sizeof(u32)));
    u32 grouping_type = *((u32 *)(Data + 4 * sizeof(u32)));
    u32 grouping_type_parameter = *((u32 *)(Data + 5 * sizeof(u32)));

    // Initialize an ISO file
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    // Prepare output variables
    u32 alternateGroupID = 0;
    u32 nb_groups = 0;
    u32 sampleGroupDescIndex = 0;

    // Call the target functions
    gf_isom_remove_sample(isom_file, trackNumber, sampleNumber);
    gf_isom_get_track_switch_group_count(isom_file, trackNumber, &alternateGroupID, &nb_groups);
    gf_isom_set_last_sample_duration(isom_file, trackNumber, duration);
    gf_isom_set_ctts_v1(isom_file, trackNumber, ctts_shift);
    gf_isom_get_sample_to_group_info(isom_file, trackNumber, sampleNumber, grouping_type, grouping_type_parameter, &sampleGroupDescIndex);

    // Clean up
    gf_isom_close(isom_file);

    // Write dummy data to a file if needed
    write_dummy_file(Data, Size);

    return 0;
}