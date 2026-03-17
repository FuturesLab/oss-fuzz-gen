// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_ismacryp_info at drm_sample.c:257:8 in isomedia.h
// gf_isom_has_padding_bits at isom_read.c:2680:6 in isomedia.h
// gf_isom_enum_track_group at isom_read.c:6457:6 in isomedia.h
// gf_isom_is_adobe_protection_media at drm_sample.c:1901:6 in isomedia.h
// gf_isom_get_sample_group_info at isom_read.c:5374:6 in isomedia.h
// gf_isom_is_track_encrypted at isom_read.c:1624:6 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_301(const uint8_t *Data, size_t Size) {
    if (Size < 4) { // Ensure we have enough data to work with
        return 0;
    }

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = 1;  // Arbitrary track number
    u32 sampleDescriptionIndex = 0;  // Arbitrary sample description index
    u32 outOriginalFormat, outSchemeType, outSchemeVersion;
    const char *outSchemeURI, *outKMS_URI;
    Bool outSelectiveEncryption;
    u32 outIVLength, outKeyIndicationLength;

    gf_isom_get_ismacryp_info(isom_file, trackNumber, sampleDescriptionIndex, &outOriginalFormat, &outSchemeType, &outSchemeVersion, &outSchemeURI, &outKMS_URI, &outSelectiveEncryption, &outIVLength, &outKeyIndicationLength);

    Bool hasPaddingBits = gf_isom_has_padding_bits(isom_file, trackNumber);

    u32 idx = 0;
    u32 track_group_type, track_group_id;
    Bool enumTrackGroup = gf_isom_enum_track_group(isom_file, trackNumber, &idx, &track_group_type, &track_group_id);

    Bool isAdobeProtected = gf_isom_is_adobe_protection_media(isom_file, trackNumber, sampleDescriptionIndex);

    u32 sample_group_description_index = 0;  // Arbitrary sample group description index
    u32 grouping_type = 0;  // Arbitrary grouping type
    u32 default_index;
    const u8 *data;
    u32 size;
    Bool getSampleGroupInfo = gf_isom_get_sample_group_info(isom_file, trackNumber, sample_group_description_index, grouping_type, &default_index, &data, &size);

    Bool isTrackEncrypted = gf_isom_is_track_encrypted(isom_file, trackNumber);

    gf_isom_close(isom_file);

    return 0;
}