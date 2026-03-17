// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open_progressive_ex at isom_read.c:435:8 in isomedia.h
// gf_isom_get_root_sidx_offsets at isom_read.c:6083:6 in isomedia.h
// gf_isom_set_single_moof_mode at isom_read.c:3144:6 in isomedia.h
// gf_isom_reset_data_offset at isom_read.c:3151:8 in isomedia.h
// gf_isom_close_segment at movie_fragments.c:1743:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

#define DUMMY_FILE_NAME "./dummy_file"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE_NAME, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isom_file = NULL;
    u64 start = 0, end = 0, BytesMissing = 0, top_box_start = 0;
    u32 topBoxType = 0;
    GF_Err err;

    // Write the input data to a dummy file to simulate file-based operations
    write_dummy_file(Data, Size);

    // Test gf_isom_open_progressive_ex
    err = gf_isom_open_progressive_ex(DUMMY_FILE_NAME, 0, Size, 0, &isom_file, &BytesMissing, &topBoxType);
    if (err == GF_OK && isom_file) {
        // Test gf_isom_get_root_sidx_offsets
        gf_isom_get_root_sidx_offsets(isom_file, &start, &end);

        // Test gf_isom_set_single_moof_mode
        gf_isom_set_single_moof_mode(isom_file, GF_TRUE);

        // Test gf_isom_reset_data_offset
        gf_isom_reset_data_offset(isom_file, &top_box_start);

        // Test gf_isom_close_segment
        u64 index_start_range = 0, index_end_range = 0, out_seg_size = 0;
        gf_isom_close_segment(isom_file, 0, 0, 0, 0, 0, GF_FALSE, GF_FALSE, GF_FALSE, GF_TRUE, 0, &index_start_range, &index_end_range, &out_seg_size);

        // Clean up
        gf_isom_close(isom_file);
    }

    return 0;
}