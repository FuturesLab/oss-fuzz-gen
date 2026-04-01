// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_sample_for_media_time at isom_read.c:2192:8 in isomedia.h
// gf_isom_set_nalu_extract_mode at isom_read.c:5481:8 in isomedia.h
// gf_isom_dump_supported_box at box_funcs.c:2293:8 in isomedia.h
// gf_isom_get_meta_image_props at meta.c:735:8 in isomedia.h
// gf_isom_add_sample_reference at isom_write.c:1269:8 in isomedia.h
// gf_isom_text_dump at box_dump.c:4470:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile *initialize_iso_file(const uint8_t *data, size_t size) {
    // Since GF_ISOFile is incomplete, we cannot allocate or initialize it directly.
    // Assume a function gf_isom_open_file exists to open and return a GF_ISOFile*.
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the dummy file as a GF_ISOFile
    GF_ISOFile *iso_file = gf_isom_open_file("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
        remove("./dummy_file");
    }
}

int LLVMFuzzerTestOneInput_237(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *iso_file = initialize_iso_file(Data, Size);
    if (!iso_file) return 0;

    // Fuzz gf_isom_get_sample_for_media_time
    u32 trackNumber = Data[0] % 256;
    u64 desiredTime = (Size > 8) ? *((u64 *)(Data + 1)) : 0;
    u32 sampleDescriptionIndex = 0;
    GF_ISOSample *sample = NULL;
    u32 sample_number = 0;
    u64 data_offset = 0;

    gf_isom_get_sample_for_media_time(iso_file, trackNumber, desiredTime, &sampleDescriptionIndex, 0, &sample, &sample_number, &data_offset);

    // Fuzz gf_isom_set_nalu_extract_mode
    GF_ISONaluExtractMode nalu_extract_mode = (GF_ISONaluExtractMode)(Data[0] % 3);
    gf_isom_set_nalu_extract_mode(iso_file, trackNumber, nalu_extract_mode);

    // Fuzz gf_isom_dump_supported_box
    FILE *trace_file = fopen("./dummy_file", "a");
    if (trace_file) {
        u32 box_index = Data[0] % 256;
        gf_isom_dump_supported_box(box_index, trace_file);
        fclose(trace_file);
    }

    // Fuzz gf_isom_get_meta_image_props
    GF_ImageItemProperties image_props;
    GF_List *unmapped_props = NULL; // Corrected to be a pointer
    gf_isom_get_meta_image_props(iso_file, 1, trackNumber, 0, &image_props, unmapped_props);

    // Fuzz gf_isom_add_sample_reference
    gf_isom_add_sample_reference(iso_file, trackNumber, sampleDescriptionIndex, sample, data_offset);

    // Fuzz gf_isom_text_dump
    GF_TextDumpType dump_type = (GF_TextDumpType)(Data[0] % 3);
    trace_file = fopen("./dummy_file", "a");
    if (trace_file) {
        gf_isom_text_dump(iso_file, trackNumber, trace_file, dump_type);
        fclose(trace_file);
    }

    cleanup_iso_file(iso_file);
    return 0;
}