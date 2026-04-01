// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_edit_list_type at isom_read.c:2504:6 in isomedia.h
// gf_isom_is_track_fragmented at movie_fragments.c:3512:6 in isomedia.h
// gf_isom_has_padding_bits at isom_read.c:2680:6 in isomedia.h
// gf_isom_get_tile_info at isom_read.c:5878:6 in isomedia.h
// gf_isom_is_track_encrypted at isom_read.c:1624:6 in isomedia.h
// gf_isom_has_sync_shadows at isom_read.c:1894:6 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32*)Data) % 100; // Arbitrary track number limit
    s64 mediaOffset = 0;

    // Fuzz gf_isom_get_edit_list_type
    Bool edit_list_type = gf_isom_get_edit_list_type(isom_file, trackNumber, &mediaOffset);

    // Fuzz gf_isom_is_track_fragmented
    Bool is_fragmented = gf_isom_is_track_fragmented(isom_file, trackNumber);

    // Fuzz gf_isom_has_padding_bits
    Bool has_padding_bits = gf_isom_has_padding_bits(isom_file, trackNumber);

    // Fuzz gf_isom_get_tile_info
    u32 default_sample_group_index = 0, id = 0, independent = 0, x = 0, y = 0, w = 0, h = 0;
    Bool full_frame = GF_FALSE;
    Bool tile_info = gf_isom_get_tile_info(isom_file, trackNumber, 0, &default_sample_group_index, &id, &independent, &full_frame, &x, &y, &w, &h);

    // Fuzz gf_isom_is_track_encrypted
    Bool is_encrypted = gf_isom_is_track_encrypted(isom_file, trackNumber);

    // Fuzz gf_isom_has_sync_shadows
    Bool has_sync_shadows = gf_isom_has_sync_shadows(isom_file, trackNumber);

    gf_isom_close(isom_file);
    return 0;
}