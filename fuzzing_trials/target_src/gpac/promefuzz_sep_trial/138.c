// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_fragment_set_sample_aux_info at isom_write.c:9290:8 in isomedia.h
// gf_isom_get_trex_template at isom_write.c:4274:8 in isomedia.h
// gf_isom_is_track_in_root_od at isom_read.c:1018:4 in isomedia.h
// gf_isom_has_sync_points at isom_read.c:2603:4 in isomedia.h
// gf_isom_is_track_enabled at isom_read.c:1054:4 in isomedia.h
// gf_isom_get_user_data_count at isom_read.c:2735:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_isofile() {
    // Since GF_ISOFile is an incomplete type, we cannot allocate it directly.
    // Instead, we assume the library provides a function to create an ISOFile.
    GF_ISOFile *isofile = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isofile;
}

static void free_dummy_isofile(GF_ISOFile *isofile) {
    if (isofile) {
        gf_isom_close(isofile);
    }
}

int LLVMFuzzerTestOneInput_138(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isofile = create_dummy_isofile();
    if (!isofile) return 0;

    // Fuzzing gf_isom_fragment_set_sample_aux_info
    u32 trackID = Data[0];
    u32 sample_number_in_frag = (Size > 1) ? Data[1] : 0;
    u32 aux_type = (Size > 2) ? Data[2] : 1; // Ensure non-zero
    u32 aux_info = (Size > 3) ? Data[3] : 0;
    u8 *aux_data = (Size > 4) ? (u8*)&Data[4] : NULL;
    u32 aux_data_size = (Size > 4) ? Size - 4 : 0;
    gf_isom_fragment_set_sample_aux_info(isofile, trackID, sample_number_in_frag, aux_type, aux_info, aux_data, aux_data_size);

    // Fuzzing gf_isom_get_trex_template
    u8 *output = NULL;
    u32 output_size = 0;
    gf_isom_get_trex_template(isofile, trackID, &output, &output_size);
    free(output);

    // Fuzzing gf_isom_is_track_in_root_od
    gf_isom_is_track_in_root_od(isofile, trackID);

    // Fuzzing gf_isom_has_sync_points
    gf_isom_has_sync_points(isofile, trackID);

    // Fuzzing gf_isom_is_track_enabled
    gf_isom_is_track_enabled(isofile, trackID);

    // Fuzzing gf_isom_get_user_data_count
    bin128 UUID = {0};
    gf_isom_get_user_data_count(isofile, trackID, aux_type, UUID);

    free_dummy_isofile(isofile);
    return 0;
}