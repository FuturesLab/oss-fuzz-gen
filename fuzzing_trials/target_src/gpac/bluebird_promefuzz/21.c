#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_set_single_moof_mode
    Bool ret_gf_isom_is_JPEG2000_qpntk = gf_isom_is_JPEG2000(NULL);

    gf_isom_set_single_moof_mode(isom_file, ret_gf_isom_is_JPEG2000_qpntk);

    // End mutation: Producer.APPEND_MUTATOR

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