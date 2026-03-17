// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_fragment_option at movie_fragments.c:476:8 in isomedia.h
// gf_isom_fragment_set_sample_flags at movie_fragments.c:3395:8 in isomedia.h
// gf_isom_set_track_reference at isom_write.c:4967:8 in isomedia.h
// gf_isom_set_fragment_original_duration at movie_fragments.c:3171:8 in isomedia.h
// gf_isom_set_sample_flags at isom_write.c:8052:8 in isomedia.h
// gf_isom_set_brand_info at isom_write.c:3520:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file() {
    GF_ISOFile* file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return file;
}

static void cleanup_iso_file(GF_ISOFile* file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_282(const uint8_t *Data, size_t Size) {
    // Write the input data to a dummy file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) return 0;
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    GF_ISOFile *isom_file = initialize_iso_file();
    if (!isom_file) return 0;

    // Fuzz gf_isom_set_fragment_option
    if (Size > 3) {
        gf_isom_set_fragment_option(isom_file, Data[0], Data[1], Data[2]);
    }

    // Fuzz gf_isom_fragment_set_sample_flags
    if (Size > 4) {
        gf_isom_fragment_set_sample_flags(isom_file, Data[0], Data[1], Data[2], Data[3], Data[4]);
    }

    // Fuzz gf_isom_set_track_reference
    if (Size > 2) {
        gf_isom_set_track_reference(isom_file, Data[0], Data[1], Data[2]);
    }

    // Fuzz gf_isom_set_fragment_original_duration
    if (Size > 3) {
        gf_isom_set_fragment_original_duration(isom_file, Data[0], Data[1], Data[2]);
    }

    // Fuzz gf_isom_set_sample_flags
    if (Size > 6) {
        gf_isom_set_sample_flags(isom_file, Data[0], Data[1], Data[2], Data[3], Data[4], Data[5]);
    }

    // Fuzz gf_isom_set_brand_info
    if (Size > 1) {
        gf_isom_set_brand_info(isom_file, Data[0], Data[1]);
    }

    cleanup_iso_file(isom_file);
    return 0;
}