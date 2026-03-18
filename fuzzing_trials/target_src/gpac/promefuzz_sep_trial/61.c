// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_remove_stream_description at isom_write.c:909:8 in isomedia.h
// gf_isom_evte_config_new at sample_descs.c:1846:8 in isomedia.h
// gf_isom_set_sample_cenc_default_group at isom_write.c:7843:8 in isomedia.h
// gf_isom_remove_sample_group at isom_write.c:7632:8 in isomedia.h
// gf_isom_set_mpegh_compatible_profiles at isom_write.c:9336:8 in isomedia.h
// gf_isom_set_last_sample_duration_ex at isom_write.c:1431:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
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

int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 6) return 0;

    // Prepare a dummy ISO file
    write_dummy_file(Data, Size);

    // Cast data to appropriate types
    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *((u32 *)Data + 1);
    u32 grouping_type = *((u32 *)Data + 2);
    u32 dur_num = *((u32 *)Data + 3);
    u32 dur_den = *((u32 *)Data + 4);
    u32 sampleNumber = *((u32 *)Data + 5);

    // Initialize a dummy ISO file structure
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    // Fuzz gf_isom_remove_stream_description
    gf_isom_remove_stream_description(isom_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_evte_config_new
    u32 outDescriptionIndex;
    gf_isom_evte_config_new(isom_file, trackNumber, &outDescriptionIndex);

    // Fuzz gf_isom_set_sample_cenc_default_group
    gf_isom_set_sample_cenc_default_group(isom_file, trackNumber, sampleNumber);

    // Fuzz gf_isom_remove_sample_group
    gf_isom_remove_sample_group(isom_file, trackNumber, grouping_type);

    // Fuzz gf_isom_set_mpegh_compatible_profiles
    gf_isom_set_mpegh_compatible_profiles(isom_file, trackNumber, sampleDescriptionIndex, NULL, 0);

    // Fuzz gf_isom_set_last_sample_duration_ex
    gf_isom_set_last_sample_duration_ex(isom_file, trackNumber, dur_num, dur_den);

    // Close and clean up
    gf_isom_close(isom_file);

    return 0;
}