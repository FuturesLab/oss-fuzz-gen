// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_set_track_magic at isom_write.c:8936:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_append_edit at isom_write.c:2849:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_modify_edit at isom_write.c:2894:8 in isomedia.h
// gf_isom_get_edit at isom_read.c:2560:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_traf_mss_timeext at movie_fragments.c:2563:8 in isomedia.h
// gf_isom_get_chunk_info at isom_read.c:6325:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    // Allocate memory for GF_ISOFile and simulate initialization
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_250(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) + sizeof(u64)) return 0;

    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return 0;

    u32 trackNumber = *((u32*)Data);
    u64 magic = *((u64*)(Data + sizeof(u32)));

    gf_isom_set_track_magic(isom_file, trackNumber, magic);

    if (Size < sizeof(u32) + 3 * sizeof(u64)) {
        gf_isom_close(isom_file);
        return 0;
    }

    u64 EditDuration = *((u64*)(Data + sizeof(u32) + sizeof(u64)));
    u64 MediaTime = *((u64*)(Data + sizeof(u32) + 2 * sizeof(u64)));
    GF_ISOEditType EditMode = (GF_ISOEditType)(Data[sizeof(u32) + 3 * sizeof(u64)] % 3);

    gf_isom_append_edit(isom_file, trackNumber, EditDuration, MediaTime, EditMode);

    if (Size < sizeof(u32) * 2 + 3 * sizeof(u64)) {
        gf_isom_close(isom_file);
        return 0;
    }

    u32 edit_index = *((u32*)(Data + sizeof(u32) + 3 * sizeof(u64)));

    gf_isom_modify_edit(isom_file, trackNumber, edit_index, EditDuration, MediaTime, EditMode);

    u64 EditTime, SegmentDuration;
    gf_isom_get_edit(isom_file, trackNumber, edit_index, &EditTime, &SegmentDuration, &MediaTime, &EditMode);

    if (Size < sizeof(u32) * 3 + 3 * sizeof(u64)) {
        gf_isom_close(isom_file);
        return 0;
    }

    GF_ISOTrackID reference_track_ID = *((GF_ISOTrackID*)(Data + sizeof(u32) * 2 + 3 * sizeof(u64)));
    u64 decode_traf_time = *((u64*)(Data + sizeof(u32) * 3 + 3 * sizeof(u64)));
    u64 traf_duration = *((u64*)(Data + sizeof(u32) * 3 + 4 * sizeof(u64)));

    gf_isom_set_traf_mss_timeext(isom_file, reference_track_ID, decode_traf_time, traf_duration);

    u64 chunk_offset;
    u32 first_sample_num, sample_per_chunk, sample_desc_idx, cache_1 = 0, cache_2 = 0;
    u32 chunkNumber = *((u32*)(Data + sizeof(u32) * 3 + 5 * sizeof(u64)));

    gf_isom_get_chunk_info(isom_file, trackNumber, chunkNumber, &chunk_offset, &first_sample_num, &sample_per_chunk, &sample_desc_idx, &cache_1, &cache_2);

    gf_isom_close(isom_file);
    return 0;
}