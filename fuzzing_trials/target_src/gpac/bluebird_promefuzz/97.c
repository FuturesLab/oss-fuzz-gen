#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile *initialize_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);
    
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + sizeof(u64) * 3 + sizeof(Double)) return 0;

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    u64 sidx_dur = 0, creationTime = 0, modificationTime = 0;
    u32 sidx_timescale = 0, trackNumber = 0, EditIndex = 0;
    u64 EditTime = 0, SegmentDuration = 0, MediaTime = 0;
    GF_ISOEditType EditMode;
    u64 bytes_removed = 0, next_dts = 0, offset = 0;
    Double start_time = 0.0;

    gf_isom_get_sidx_duration(isom_file, &sidx_dur, &sidx_timescale);
    gf_isom_get_creation_time(isom_file, &creationTime, &modificationTime);
    gf_isom_get_edit(isom_file, trackNumber, EditIndex, &EditTime, &SegmentDuration, &MediaTime, &EditMode);
    gf_isom_set_removed_bytes(isom_file, bytes_removed);
    gf_isom_patch_last_sample_duration(isom_file, trackNumber, next_dts);
    gf_isom_get_file_offset_for_time(isom_file, start_time, &offset);

    gf_isom_close(isom_file);
    return 0;
}