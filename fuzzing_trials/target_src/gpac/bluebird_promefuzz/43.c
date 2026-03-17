#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

#define DUMMY_FILE_PATH "./dummy_file"

// Function prototypes for helper functions
static GF_ISOFile* initialize_iso_file();
static void cleanup_iso_file(GF_ISOFile* isom_file);
static void write_dummy_data_to_file(const char* filepath, const uint8_t* data, size_t size);

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 18) {
        return 0;
    }

    // Initialize the ISO file
    GF_ISOFile* isom_file = initialize_iso_file();
    if (!isom_file) {
        return 0;
    }

    // Write dummy data to file
    write_dummy_data_to_file(DUMMY_FILE_PATH, Data, Size);

    // Prepare dummy values for the API functions
    GF_ISOTrackID track_id = Data[0];
    u32 default_sample_description_index = Data[1];
    u32 default_sample_duration = Data[2];
    u32 default_sample_size = Data[3];
    u8 default_sample_sync_flags = Data[4];
    u8 default_sample_padding = Data[5];
    u16 default_degradation_priority = Data[6];
    Bool force_traf_flags = Data[7] % 2;

    u32 track_number = Data[8];
    u8 packing_bit = Data[9] % 2;
    u8 extension_bit = Data[10] % 2;
    u8 marker_bit = Data[11] % 2;
    u8 disposable_packet = Data[12] % 2;
    u8 is_repeated_packet = Data[13] % 2;

    u32 sample_number = Data[14];
    u16 data_length = Data[15];
    u32 offset_in_sample = Data[16];
    u8 at_begin = Data[17] % 2;

    u8 extra_data[14];
    size_t extra_data_size = (Size > 32) ? 14 : Size - 18;
    memcpy(extra_data, Data + 18, extra_data_size);

    // Call the target API functions with diverse inputs
    gf_isom_setup_track_fragment(isom_file, track_id, default_sample_description_index, default_sample_duration, default_sample_size, default_sample_sync_flags, default_sample_padding, default_degradation_priority, force_traf_flags);

    gf_isom_rtp_packet_set_flags(isom_file, track_number, packing_bit, extension_bit, marker_bit, disposable_packet, is_repeated_packet);

    gf_isom_hint_sample_data(isom_file, track_number, track_id, sample_number, data_length, offset_in_sample, extra_data, at_begin);

    gf_isom_hint_direct_data(isom_file, track_number, extra_data, extra_data_size, at_begin);

    gf_isom_hint_blank_data(isom_file, track_number, at_begin);

    gf_isom_add_user_data_boxes(isom_file, track_number, extra_data, extra_data_size);

    // Cleanup
    cleanup_iso_file(isom_file);

    return 0;
}

static GF_ISOFile* initialize_iso_file() {
    GF_ISOFile* isom_file = gf_isom_open(DUMMY_FILE_PATH, GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile* isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

static void write_dummy_data_to_file(const char* filepath, const uint8_t* data, size_t size) {
    FILE* file = fopen(filepath, "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}