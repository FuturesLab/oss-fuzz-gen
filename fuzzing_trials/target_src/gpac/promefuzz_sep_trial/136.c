// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_append_edit at isom_write.c:2849:8 in isomedia.h
// gf_isom_set_edit_with_rate at isom_write.c:2789:8 in isomedia.h
// gf_isom_modify_edit at isom_write.c:2894:8 in isomedia.h
// gf_isom_patch_last_sample_duration at isom_write.c:1425:8 in isomedia.h
// gf_isom_get_edit at isom_read.c:2560:8 in isomedia.h
// gf_isom_set_edit at isom_write.c:2783:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile *create_dummy_iso_file() {
    // Allocate memory for the GF_ISOFile structure through an appropriate initializer
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return file;
}

static void cleanup_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_136(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isoFile = create_dummy_iso_file();
    if (!isoFile) return 0;

    u32 trackNumber = Data[0];
    u64 EditDuration = Size > 8 ? *(u64 *)(Data + 1) : 0;
    u64 MediaTime = Size > 16 ? *(u64 *)(Data + 9) : 0;
    GF_ISOEditType EditMode = Size > 24 ? (GF_ISOEditType)Data[17] : 0;
    u64 EditTime = Size > 32 ? *(u64 *)(Data + 25) : 0;
    u32 MediaRate = Size > 40 ? *(u32 *)(Data + 33) : 0;
    u64 next_dts = Size > 48 ? *(u64 *)(Data + 41) : 0;
    u32 edit_index = Size > 56 ? *(u32 *)(Data + 49) : 0;

    // Fuzz gf_isom_append_edit
    gf_isom_append_edit(isoFile, trackNumber, EditDuration, MediaTime, EditMode);

    // Fuzz gf_isom_set_edit_with_rate
    gf_isom_set_edit_with_rate(isoFile, trackNumber, EditTime, EditDuration, MediaTime, MediaRate);

    // Fuzz gf_isom_modify_edit
    gf_isom_modify_edit(isoFile, trackNumber, edit_index, EditDuration, MediaTime, EditMode);

    // Fuzz gf_isom_patch_last_sample_duration
    gf_isom_patch_last_sample_duration(isoFile, trackNumber, next_dts);

    // Fuzz gf_isom_get_edit
    u64 EditTimeOut = 0, SegmentDurationOut = 0, MediaTimeOut = 0;
    GF_ISOEditType EditModeOut = 0;
    gf_isom_get_edit(isoFile, trackNumber, edit_index, &EditTimeOut, &SegmentDurationOut, &MediaTimeOut, &EditModeOut);

    // Fuzz gf_isom_set_edit
    gf_isom_set_edit(isoFile, trackNumber, EditTime, EditDuration, MediaTime, EditMode);

    cleanup_iso_file(isoFile);
    return 0;
}