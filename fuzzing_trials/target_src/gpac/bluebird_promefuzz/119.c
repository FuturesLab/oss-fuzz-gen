#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5 + sizeof(s32)) {
        return 0;
    }

    // Prepare the environment
    GF_ISOFile *isom_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    // Initialize parameters
    u32 trackNumber = *((u32 *)Data);
    u32 sampleNumber = *((u32 *)(Data + 4));
    u32 grouping_type = *((u32 *)(Data + 8));
    u32 sampleGroupDescriptionIndex = *((u32 *)(Data + 12));
    u32 grouping_type_parameter = *((u32 *)(Data + 16));
    s32 ID = *((s32 *)(Data + 20));

    // Write dummy file
    write_dummy_file(Data, Size);

    // Fuzz gf_isom_fragment_add_sample_references
    s32 *refs = (s32 *)malloc(sizeof(s32) * Size);
    if (refs) {
        for (size_t i = 0; i < Size / sizeof(s32); i++) {
            refs[i] = (s32)Data[i];
        }
        gf_isom_fragment_add_sample_references(isom_file, trackNumber, ID, Size / sizeof(s32), refs);
        free(refs);
    }

    // Fuzz gf_isom_add_sample_info
    gf_isom_add_sample_info(isom_file, trackNumber, sampleNumber, grouping_type, sampleGroupDescriptionIndex, grouping_type_parameter);

    // Fuzz gf_isom_get_reference_count
    gf_isom_get_reference_count(isom_file, trackNumber, grouping_type);

    // Fuzz gf_isom_set_sample_references
    gf_isom_set_sample_references(isom_file, trackNumber, sampleNumber, ID, Size / sizeof(s32), refs);

    // Fuzz gf_isom_set_track_reference
    gf_isom_set_track_reference(isom_file, trackNumber, grouping_type, trackNumber);

    // Fuzz gf_isom_get_sample_flags
    u32 is_leading, dependsOn, dependedOn, redundant;
    gf_isom_get_sample_flags(isom_file, trackNumber, sampleNumber, &is_leading, &dependsOn, &dependedOn, &redundant);

    // Cleanup
    gf_isom_close(isom_file);

    return 0;
}