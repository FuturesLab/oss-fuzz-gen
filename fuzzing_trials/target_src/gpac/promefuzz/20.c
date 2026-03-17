// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_change_track_fragment_defaults at movie_fragments.c:216:8 in isomedia.h
// gf_isom_set_media_subtype at isom_write.c:6197:8 in isomedia.h
// gf_isom_update_sample_description_from_template at isom_write.c:8597:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_visual_color_info at isom_write.c:1890:8 in isomedia.h
// gf_isom_set_track_stsd_templates at isom_write.c:835:8 in isomedia.h
// gf_isom_hint_sample_description_data at hint_track.c:539:8 in isomedia.h
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

int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + sizeof(u16) * 3 + sizeof(Bool) + sizeof(u32) * 3 + sizeof(u8)) {
        return 0;
    }

    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ_EDIT, NULL);
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    Data += sizeof(u32);
    Size -= sizeof(u32);

    u32 sampleDescriptionIndex = *((u32 *)Data);
    Data += sizeof(u32);
    Size -= sizeof(u32);

    u32 colour_type = *((u32 *)Data);
    Data += sizeof(u32);
    Size -= sizeof(u32);

    u16 colour_primaries = *((u16 *)Data);
    Data += sizeof(u16);
    Size -= sizeof(u16);

    u16 transfer_characteristics = *((u16 *)Data);
    Data += sizeof(u16);
    Size -= sizeof(u16);

    u16 matrix_coefficients = *((u16 *)Data);
    Data += sizeof(u16);
    Size -= sizeof(u16);

    Bool full_range_flag = *((Bool *)Data);
    Data += sizeof(Bool);
    Size -= sizeof(Bool);

    u32 icc_size = *((u32 *)Data);
    icc_size = icc_size % (Size + 1); // Ensure icc_size is within bounds
    Data += sizeof(u32);
    Size -= sizeof(u32);

    u32 stsd_data_size = *((u32 *)Data);
    stsd_data_size = stsd_data_size % (Size + 1); // Ensure stsd_data_size is within bounds
    Data += sizeof(u32);
    Size -= sizeof(u32);

    u32 new_type = *((u32 *)Data);
    Data += sizeof(u32);
    Size -= sizeof(u32);

    u8 AtBegin = *Data;
    Data += sizeof(u8);
    Size -= sizeof(u8);

    u8 *icc_data = (u8 *)malloc(icc_size);
    if (!icc_data) {
        gf_isom_close(isom_file);
        return 0;
    }
    memcpy(icc_data, Data, icc_size);

    u8 *stsd_data = (u8 *)malloc(stsd_data_size);
    if (!stsd_data) {
        free(icc_data);
        gf_isom_close(isom_file);
        return 0;
    }
    memcpy(stsd_data, Data, stsd_data_size);

    GF_Err err;

    err = gf_isom_set_visual_color_info(isom_file, trackNumber, sampleDescriptionIndex, colour_type, 
                                        colour_primaries, transfer_characteristics, matrix_coefficients, 
                                        full_range_flag, icc_data, icc_size);

    err = gf_isom_set_track_stsd_templates(isom_file, trackNumber, stsd_data, stsd_data_size);

    u16 DataLength = (u16)(Size % 65536);
    u32 offsetInDescription = 0;
    err = gf_isom_hint_sample_description_data(isom_file, trackNumber, trackNumber, sampleDescriptionIndex, 
                                               DataLength, offsetInDescription, AtBegin);

    u32 DefaultSampleDescriptionIndex = 0;
    u32 DefaultSampleDuration = 0;
    u32 DefaultSampleSize = 0;
    u8 DefaultSampleIsSync = 0;
    u8 DefaultSamplePadding = 0;
    u16 DefaultDegradationPriority = 0;
    u8 force_traf_flags = 0;
    err = gf_isom_change_track_fragment_defaults(isom_file, trackNumber, DefaultSampleDescriptionIndex, 
                                                 DefaultSampleDuration, DefaultSampleSize, DefaultSampleIsSync, 
                                                 DefaultSamplePadding, DefaultDegradationPriority, force_traf_flags);

    err = gf_isom_set_media_subtype(isom_file, trackNumber, sampleDescriptionIndex, new_type);

    err = gf_isom_update_sample_description_from_template(isom_file, trackNumber, sampleDescriptionIndex, 
                                                          stsd_data, stsd_data_size);

    free(icc_data);
    free(stsd_data);
    gf_isom_close(isom_file);
    return 0;
}