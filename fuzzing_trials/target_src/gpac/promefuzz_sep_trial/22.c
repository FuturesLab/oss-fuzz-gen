// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_guess_specification at isom_read.c:4276:5 in isomedia.h
// gf_isom_get_copyright_count at isom_read.c:1473:5 in isomedia.h
// gf_isom_set_next_moof_number at movie_fragments.c:3474:6 in isomedia.h
// gf_isom_get_brands at isom_read.c:2657:12 in isomedia.h
// gf_isom_get_audio_info at isom_read.c:3880:8 in isomedia.h
// gf_isom_get_track_kind_count at isom_read.c:1136:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile *create_dummy_isofile() {
    // Allocate a dummy buffer to simulate the GF_ISOFile structure
    size_t dummy_size = 1024;
    GF_ISOFile *isom_file = (GF_ISOFile *)malloc(dummy_size);
    if (!isom_file) return NULL;
    memset(isom_file, 0, dummy_size);
    return isom_file;
}

static void destroy_dummy_isofile(GF_ISOFile *isom_file) {
    if (isom_file) {
        free(isom_file);
    }
}

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return 0;

    // Fuzz gf_isom_guess_specification
    u32 brand = gf_isom_guess_specification(isom_file);

    // Fuzz gf_isom_get_copyright_count
    u32 copyright_count = gf_isom_get_copyright_count(isom_file);

    // Fuzz gf_isom_set_next_moof_number
    if (Size >= sizeof(u32)) {
        u32 moof_number = *((u32 *)Data);
        gf_isom_set_next_moof_number(isom_file, moof_number);
    }

    // Fuzz gf_isom_get_brands
    const u32 *brands = gf_isom_get_brands(isom_file);

    // Fuzz gf_isom_get_audio_info
    if (Size >= 3 * sizeof(u32)) {
        u32 trackNumber = *((u32 *)Data);
        u32 sampleDescriptionIndex = *(((u32 *)Data) + 1);
        u32 SampleRate, Channels, bitsPerSample;
        GF_Err audio_info_err = gf_isom_get_audio_info(
            isom_file, trackNumber, sampleDescriptionIndex, &SampleRate, &Channels, &bitsPerSample
        );
    }

    // Fuzz gf_isom_get_track_kind_count
    if (Size >= sizeof(u32)) {
        u32 trackNumber = *((u32 *)Data);
        u32 kind_count = gf_isom_get_track_kind_count(isom_file, trackNumber);
    }

    destroy_dummy_isofile(isom_file);
    return 0;
}