#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // GF_ISOFile is an incomplete type, so we cannot allocate it directly.
    // Assume we have a function to create or mock a GF_ISOFile.
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
}

static void free_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

static void fuzz_gf_isom_get_raw_user_data(GF_ISOFile *file) {
    u8 *output = NULL;
    u32 output_size = 0;
    GF_Err err = gf_isom_get_raw_user_data(file, &output, &output_size);
    if (err == GF_OK && output) {
        free(output);
    }
}

static void fuzz_gf_isom_fragment_append_data(GF_ISOFile *file, const uint8_t *Data, size_t Size) {
    if (Size < 4) return; // Ensure there's enough data for TrackID and PaddingBits
    GF_ISOTrackID TrackID = *(GF_ISOTrackID *)Data;
    u8 PaddingBits = Data[Size - 1];
    gf_isom_fragment_append_data(file, TrackID, (u8 *)Data, (u32)Size, PaddingBits);
}

static void fuzz_gf_isom_get_trex_template(GF_ISOFile *file, const uint8_t *Data, size_t Size) {
    if (Size < 4) return; // Ensure there's enough data for trackNumber
    u32 trackNumber = *(u32 *)Data;
    u8 *output = NULL;
    u32 output_size = 0;
    GF_Err err = gf_isom_get_trex_template(file, trackNumber, &output, &output_size);
    if (err == GF_OK && output) {
        free(output);
    }
}

static void fuzz_gf_isom_add_uuid(GF_ISOFile *file, const uint8_t *Data, size_t Size) {
    if (Size < 16) return; // Ensure there's enough data for UUID
    u32 trackNumber = *(u32 *)Data;
    bin128 UUID;
    memcpy(UUID, Data + 4, 16);
    const u8 *data = (Size > 20) ? Data + 20 : NULL;
    u32 size = (Size > 20) ? (u32)(Size - 20) : 0;
    gf_isom_add_uuid(file, trackNumber, UUID, data, size);
}

static void fuzz_gf_isom_set_track_stsd_templates(GF_ISOFile *file, const uint8_t *Data, size_t Size) {
    if (Size < 4) return; // Ensure there's enough data for trackNumber
    u32 trackNumber = *(u32 *)Data;
    u8 *stsd_data = (u8 *)(Data + 4);
    u32 stsd_data_size = (u32)(Size - 4);
    gf_isom_set_track_stsd_templates(file, trackNumber, stsd_data, stsd_data_size);
}

static void fuzz_gf_isom_update_sample_description_from_template(GF_ISOFile *file, const uint8_t *Data, size_t Size) {
    if (Size < 8) return; // Ensure there's enough data for trackNumber and sampleDescriptionIndex
    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + 4);
    u8 *data = (u8 *)(Data + 8);
    u32 size = (u32)(Size - 8);
    gf_isom_update_sample_description_from_template(file, trackNumber, sampleDescriptionIndex, data, size);
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    GF_ISOFile *file = create_dummy_iso_file();
    if (!file) return 0;

    fuzz_gf_isom_get_raw_user_data(file);
    fuzz_gf_isom_fragment_append_data(file, Data, Size);
    fuzz_gf_isom_get_trex_template(file, Data, Size);
    fuzz_gf_isom_add_uuid(file, Data, Size);
    fuzz_gf_isom_set_track_stsd_templates(file, Data, Size);
    fuzz_gf_isom_update_sample_description_from_template(file, Data, Size);

    free_iso_file(file);
    return 0;
}