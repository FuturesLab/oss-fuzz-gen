#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* open_dummy_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return NULL;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Assuming we have a function to open an ISO file from a file path.
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void close_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < 4) {
        return 0;
    }

    GF_ISOFile *isom_file = open_dummy_iso_file(Data, Size);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = Data[0] % 256; // Simple way to get a track number
    u32 sampleDescriptionIndex = Data[1] % 256; // Simple way to get a sample description index

    // Fuzz gf_isom_get_avg_sample_delta
    u32 avg_sample_delta = gf_isom_get_avg_sample_delta(isom_file, trackNumber);

    // Fuzz gf_isom_get_payt_count
    u32 payt_count = gf_isom_get_payt_count(isom_file, trackNumber);

    // Fuzz gf_isom_get_track_count
    u32 track_count = gf_isom_get_track_count(isom_file);

    // Fuzz gf_isom_get_track_kind_count

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_track_kind_count with gf_isom_get_media_timescale
    u32 track_kind_count = gf_isom_get_media_timescale(isom_file, trackNumber);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_get_sample_count
    u32 sample_count = gf_isom_get_sample_count(isom_file, trackNumber);

    // Fuzz gf_isom_get_vvc_type
    GF_ISOMVVCType vvc_type = gf_isom_get_vvc_type(isom_file, trackNumber, sampleDescriptionIndex);

    close_iso_file(isom_file);
    return 0;
}