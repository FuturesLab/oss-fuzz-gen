// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_is_track_fragmented at movie_fragments.c:3512:6 in isomedia.h
// gf_isom_is_cenc_media at drm_sample.c:681:6 in isomedia.h
// gf_isom_is_self_contained at isom_read.c:2158:6 in isomedia.h
// gf_isom_has_padding_bits at isom_read.c:2680:6 in isomedia.h
// gf_isom_enable_raw_pack at isom_read.c:1799:6 in isomedia.h
// gf_isom_is_track_encrypted at isom_read.c:1624:6 in isomedia.h
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

#define DUMMY_FILE_PATH "./dummy_file"

static GF_ISOFile* create_dummy_iso_file(const uint8_t *Data, size_t Size) {
    // Write the data to a dummy file
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file as a GF_ISOFile
    GF_ISOFile *iso_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void close_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_95(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file(Data, Size);
    if (!iso_file) return 0;

    u32 trackNumber = *(u32*)Data;
    u32 sampleDescriptionIndex = *((u32*)Data + 1);
    u32 pack_num_samples = *((u32*)Data + 2);

    // Fuzz gf_isom_is_track_fragmented
    gf_isom_is_track_fragmented(iso_file, trackNumber);

    // Fuzz gf_isom_is_cenc_media
    gf_isom_is_cenc_media(iso_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_is_self_contained
    gf_isom_is_self_contained(iso_file, trackNumber, sampleDescriptionIndex);

    // Fuzz gf_isom_has_padding_bits
    gf_isom_has_padding_bits(iso_file, trackNumber);

    // Fuzz gf_isom_enable_raw_pack
    gf_isom_enable_raw_pack(iso_file, trackNumber, pack_num_samples);

    // Fuzz gf_isom_is_track_encrypted
    gf_isom_is_track_encrypted(iso_file, trackNumber);

    close_iso_file(iso_file);
    return 0;
}