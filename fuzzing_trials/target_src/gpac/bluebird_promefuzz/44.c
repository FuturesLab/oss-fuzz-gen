#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

static GF_ISOFile* initialize_iso_file() {
    // Allocate memory for the GF_ISOFile structure
    GF_ISOFile *isom_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (!isom_file) return;
    gf_isom_close(isom_file);
}

int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize the ISO file
    GF_ISOFile *isom_file = initialize_iso_file();
    if (!isom_file) return 0;

    // Prepare dummy file
    FILE *dummy_file = fopen(DUMMY_FILE_PATH, "wb");
    if (!dummy_file) {
        cleanup_iso_file(isom_file);
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    // Extract parameters from the input data
    u32 trackNumber = Data[0];
    u64 EditDuration = Size > 8 ? *((u64*)(Data + 1)) : 0;
    u64 MediaTime = Size > 16 ? *((u64*)(Data + 9)) : 0;
    GF_ISOEditType EditMode = Size > 17 ? (GF_ISOEditType)Data[17] : 0;
    u64 EditTime = Size > 25 ? *((u64*)(Data + 18)) : 0;
    u32 MediaRate = Size > 29 ? *((u32*)(Data + 26)) : 0;
    u32 EditIndex = Size > 33 ? *((u32*)(Data + 30)) : 1;
    u64 trackDuration = Size > 41 ? *((u64*)(Data + 34)) : 0;

    // Variables for output parameters
    u64 outEditTime, outSegmentDuration, outMediaTime;
    GF_ISOEditType outEditMode;

    // Test gf_isom_append_edit
    gf_isom_append_edit(isom_file, trackNumber, EditDuration, MediaTime, EditMode);

    // Test gf_isom_set_edit
    gf_isom_set_edit(isom_file, trackNumber, EditTime, EditDuration, MediaTime, EditMode);

    // Test gf_isom_get_edit
    gf_isom_get_edit(isom_file, trackNumber, EditIndex, &outEditTime, &outSegmentDuration, &outMediaTime, &outEditMode);

    // Test gf_isom_set_edit_with_rate
    gf_isom_set_edit_with_rate(isom_file, trackNumber, EditTime, EditDuration, MediaTime, MediaRate);

    // Test gf_isom_force_track_duration
    gf_isom_force_track_duration(isom_file, trackNumber, trackDuration);

    // Test gf_isom_modify_edit
    gf_isom_modify_edit(isom_file, trackNumber, EditIndex, EditDuration, MediaTime, EditMode);

    // Cleanup
    cleanup_iso_file(isom_file);

    return 0;
}