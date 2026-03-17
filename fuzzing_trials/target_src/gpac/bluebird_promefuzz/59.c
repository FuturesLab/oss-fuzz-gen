#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_iso_file() {
    // Assuming GF_ISOFile is managed by the library and does not need direct allocation
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void destroy_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least some data

    GF_ISOFile *isom_file = create_iso_file();
    if (!isom_file) return 0;

    // Fuzz gf_isom_text_set_streaming_mode
    Bool do_convert = Data[0] % 2;
    gf_isom_text_set_streaming_mode(isom_file, do_convert);

    // Fuzz gf_isom_reset_tables
    Bool reset_sample_count = Data[0] % 2;
    gf_isom_reset_tables(isom_file, reset_sample_count);

    // Fuzz gf_isom_avc_set_inband_config
    if (Size >= 9) {
        u32 trackNumber = (Data[1] << 24) | (Data[2] << 16) | (Data[3] << 8) | Data[4];
        u32 sampleDescriptionIndex = (Data[5] << 24) | (Data[6] << 16) | (Data[7] << 8) | Data[8];
        Bool keep_xps = Data[0] % 2;
        gf_isom_avc_set_inband_config(isom_file, trackNumber, sampleDescriptionIndex, keep_xps);
    }

    // Fuzz gf_isom_force_64bit_chunk_offset
    Bool set_on = Data[0] % 2;
    gf_isom_force_64bit_chunk_offset(isom_file, set_on);

    // Fuzz gf_isom_start_segment
    const char *SegName = (Size > 10) ? "_gpac_isobmff_redirect" : NULL;
    Bool memory_mode = Data[0] % 2;
    gf_isom_start_segment(isom_file, SegName, memory_mode);

    // Fuzz gf_isom_release_segment
    Bool reset_tables = Data[0] % 2;
    gf_isom_release_segment(isom_file, reset_tables);

    destroy_iso_file(isom_file);
    return 0;
}