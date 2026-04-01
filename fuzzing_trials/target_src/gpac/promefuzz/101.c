// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_has_segment at isom_read.c:843:6 in isomedia.h
// gf_isom_has_cenc_sample_group at isom_read.c:5020:6 in isomedia.h
// gf_isom_enum_track_group at isom_read.c:6457:6 in isomedia.h
// gf_isom_is_track_encrypted at isom_read.c:1624:6 in isomedia.h
// gf_isom_is_ismacryp_media at drm_sample.c:218:6 in isomedia.h
// gf_isom_is_omadrm_media at drm_sample.c:237:6 in isomedia.h
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

#define DUMMY_FILE_PATH "./dummy_file"

static GF_ISOFile* create_dummy_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *isom_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file(Data, Size);
    if (!isom_file) return 0;

    u32 brand = 0, version = 0;
    gf_isom_has_segment(isom_file, &brand, &version);

    u32 trackNumber = *(u32*)Data;
    Bool has_selective = GF_FALSE, has_roll = GF_FALSE;
    gf_isom_has_cenc_sample_group(isom_file, trackNumber, &has_selective, &has_roll);

    u32 idx = 0, track_group_type = 0, track_group_id = 0;
    gf_isom_enum_track_group(isom_file, trackNumber, &idx, &track_group_type, &track_group_id);

    gf_isom_is_track_encrypted(isom_file, trackNumber);

    if (Size >= sizeof(u32) * 2) {
        u32 sampleDescriptionIndex = *((u32*)Data + 1);
        gf_isom_is_ismacryp_media(isom_file, trackNumber, sampleDescriptionIndex);
        gf_isom_is_omadrm_media(isom_file, trackNumber, sampleDescriptionIndex);
    }

    gf_isom_close(isom_file);
    return 0;
}