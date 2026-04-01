// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_guess_specification at isom_read.c:4276:5 in isomedia.h
// gf_isom_find_od_id_for_track at media_odf.c:511:5 in isomedia.h
// gf_isom_get_edits_count at isom_read.c:2547:5 in isomedia.h
// gf_isom_get_constant_sample_duration at isom_read.c:1789:5 in isomedia.h
// gf_isom_avs3v_config_get at avc_ext.c:2640:17 in isomedia.h
// gf_isom_get_brands at isom_read.c:2657:12 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file(const uint8_t *Data, size_t Size) {
    // Create a dummy file with the input data
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;

    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the ISO file using gpac API (assuming such a function exists)
    GF_ISOFile *isoFile = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isoFile;
}

static void cleanup_iso_file(GF_ISOFile *isoFile) {
    if (isoFile) {
        // Close the ISO file using gpac API (assuming such a function exists)
        gf_isom_close(isoFile);
        // Remove the dummy file
        remove("./dummy_file");
    }
}

int LLVMFuzzerTestOneInput_158(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *isoFile = create_dummy_iso_file(Data, Size);
    if (!isoFile) return 0;

    // Fuzz gf_isom_guess_specification
    u32 brand = gf_isom_guess_specification(isoFile);

    // Fuzz gf_isom_find_od_id_for_track
    u32 trackNumber = *(u32 *)Data;
    u32 od_id = gf_isom_find_od_id_for_track(isoFile, trackNumber);

    // Fuzz gf_isom_get_edits_count
    u32 edits_count = gf_isom_get_edits_count(isoFile, trackNumber);

    // Fuzz gf_isom_get_constant_sample_duration
    u32 sample_duration = gf_isom_get_constant_sample_duration(isoFile, trackNumber);

    // Fuzz gf_isom_avs3v_config_get
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    GF_AVS3VConfig *avs3_config = gf_isom_avs3v_config_get(isoFile, trackNumber, sampleDescriptionIndex);
    if (avs3_config) {
        free(avs3_config);
    }

    // Fuzz gf_isom_get_brands
    const u32 *brands = gf_isom_get_brands(isoFile);

    // Cleanup
    cleanup_iso_file(isoFile);

    return 0;
}