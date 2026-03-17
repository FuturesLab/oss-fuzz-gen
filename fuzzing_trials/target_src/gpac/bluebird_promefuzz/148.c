#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Allocate memory for GF_ISOFile and initialize required fields
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return file;
}

static void cleanup_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_148(const uint8_t *Data, size_t Size) {
    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Fuzz gf_isom_freeze_order
    gf_isom_freeze_order(iso_file);

    // Fuzz gf_isom_update_duration
    gf_isom_update_duration(iso_file);

    // Fuzz gf_isom_can_access_movie
    if (Size > 0) {
        GF_ISOOpenMode mode = Data[0] % 3; // Assuming 3 modes for simplicity
        gf_isom_can_access_movie(iso_file, mode);
    }

    // Fuzz gf_isom_reset_tables
    Bool reset_sample_count = Size > 1 ? Data[1] % 2 : 0;
    gf_isom_reset_tables(iso_file, reset_sample_count);

    // Fuzz gf_isom_start_fragment
    GF_ISOStartFragmentFlags moof_first = Size > 2 ? Data[2] % 2 : 0;
    gf_isom_start_fragment(iso_file, moof_first);

    // Fuzz gf_isom_last_error
    gf_isom_last_error(iso_file);

    cleanup_iso_file(iso_file);
    return 0;
}