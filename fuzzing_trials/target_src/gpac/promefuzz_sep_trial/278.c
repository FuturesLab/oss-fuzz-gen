// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_remove_track_from_root_od at isom_write.c:179:8 in isomedia.h
// gf_isom_set_inplace_padding at isom_read.c:88:8 in isomedia.h
// gf_isom_remove_track at isom_write.c:2942:8 in isomedia.h
// gf_isom_refresh_size_info at stbl_write.c:2299:8 in isomedia.h
// gf_isom_set_extraction_slc at isom_write.c:5927:8 in isomedia.h
// gf_isom_purge_samples at isom_read.c:3192:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* initialize_isom_file() {
    // As we cannot fully define GF_ISOFile due to its incomplete type, we assume an allocation function
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void cleanup_isom_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_278(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isom_file = initialize_isom_file();
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 padding = *((u32 *)(Data + sizeof(u32)));
    u32 nb_samples = *((u32 *)(Data + 2 * sizeof(u32)));
    u32 sampleDescriptionIndex = 0; // Default value for sample description index

    GF_SLConfig slConfig;
    slConfig.predefined = 0;

    // Fuzz gf_isom_remove_track_from_root_od
    gf_isom_remove_track_from_root_od(isom_file, trackNumber);

    // Fuzz gf_isom_set_inplace_padding
    gf_isom_set_inplace_padding(isom_file, padding);

    // Fuzz gf_isom_remove_track
    gf_isom_remove_track(isom_file, trackNumber);

    // Fuzz gf_isom_refresh_size_info
    gf_isom_refresh_size_info(isom_file, trackNumber);

    // Fuzz gf_isom_set_extraction_slc
    gf_isom_set_extraction_slc(isom_file, trackNumber, sampleDescriptionIndex, &slConfig);

    // Fuzz gf_isom_purge_samples
    gf_isom_purge_samples(isom_file, trackNumber, nb_samples);

    cleanup_isom_file(isom_file);
    return 0;
}