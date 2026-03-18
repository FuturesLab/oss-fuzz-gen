// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_set_sample_group_description at isom_write.c:7626:8 in isomedia.h
// gf_isom_set_last_sample_duration_ex at isom_write.c:1431:8 in isomedia.h
// gf_isom_copy_sample_info at isom_write.c:8078:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_fragment_set_sample_flags at movie_fragments.c:3395:8 in isomedia.h
// gf_isom_set_mpegh_compatible_profiles at isom_write.c:9336:8 in isomedia.h
// gf_isom_set_dolby_vision_profile at isom_write.c:1951:8 in isomedia.h
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

int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 16) {
        return 0;
    }

    GF_ISOFile *isom_file = NULL;
    GF_ISOFile *dst = NULL;
    GF_ISOFile *src = NULL;

    // Simulate opening an ISO file
    isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) return 0;

    dst = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!dst) {
        gf_isom_close(isom_file);
        return 0;
    }

    src = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!src) {
        gf_isom_close(isom_file);
        gf_isom_close(dst);
        return 0;
    }

    u32 offset = 0;

    GF_ISOTrackID trackID = *(GF_ISOTrackID *)(Data + offset);
    offset += sizeof(GF_ISOTrackID);

    u32 is_leading = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    u32 dependsOn = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    u32 dependedOn = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    u32 redundant = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    gf_isom_fragment_set_sample_flags(isom_file, trackID, is_leading, dependsOn, dependedOn, redundant);

    u32 trackNumber = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    u32 sampleDescriptionIndex = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    const u32 *profiles = NULL;
    u32 nb_compatible_profiles = 0;

    if (Size > offset + sizeof(u32)) {
        profiles = (const u32 *)(Data + offset);
        nb_compatible_profiles = (Size - offset) / sizeof(u32);
    }

    gf_isom_set_mpegh_compatible_profiles(isom_file, trackNumber, sampleDescriptionIndex, profiles, nb_compatible_profiles);

    GF_DOVIDecoderConfigurationRecord *dvcc = NULL;
    if (Size > offset + sizeof(GF_DOVIDecoderConfigurationRecord)) {
        dvcc = (GF_DOVIDecoderConfigurationRecord *)(Data + offset);
    }

    gf_isom_set_dolby_vision_profile(isom_file, trackNumber, sampleDescriptionIndex, dvcc);

    u32 sampleNumber = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    u32 grouping_type = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    u32 grouping_type_parameter = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    void *data = NULL;
    u32 data_size = 0;

    if (Size > offset) {
        data = (void *)(Data + offset);
        data_size = Size - offset;
    }

    u32 sgpd_flags = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    gf_isom_set_sample_group_description(isom_file, trackNumber, sampleNumber, grouping_type, grouping_type_parameter, data, data_size, sgpd_flags);

    u32 dur_num = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    u32 dur_den = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    gf_isom_set_last_sample_duration_ex(isom_file, trackNumber, dur_num, dur_den);

    u32 dst_track = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    u32 src_track = *(u32 *)(Data + offset);
    offset += sizeof(u32);

    gf_isom_copy_sample_info(dst, dst_track, src, src_track, sampleNumber);

    // Cleanup
    gf_isom_close(isom_file);
    gf_isom_close(dst);
    gf_isom_close(src);

    return 0;
}