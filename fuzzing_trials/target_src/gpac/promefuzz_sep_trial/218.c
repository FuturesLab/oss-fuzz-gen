// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_add_sample at isom_write.c:1061:8 in isomedia.h
// gf_isom_sample_del at isom_read.c:109:6 in isomedia.h
// gf_isom_get_track_template at isom_write.c:4137:8 in isomedia.h
// gf_isom_add_sample_reference at isom_write.c:1269:8 in isomedia.h
// gf_isom_fragment_add_sample at movie_fragments.c:2998:8 in isomedia.h
// gf_isom_text_to_sample at tx3g.c:472:15 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOSample* create_sample() {
    GF_ISOSample *sample = (GF_ISOSample *)malloc(sizeof(GF_ISOSample));
    if (sample) {
        memset(sample, 0, sizeof(GF_ISOSample));
    }
    return sample;
}

static GF_ISOFile* create_iso_file() {
    // Allocate a dummy buffer for GF_ISOFile as we don't have its full definition
    GF_ISOFile *iso_file = (GF_ISOFile *)malloc(1); // Allocate minimal memory
    return iso_file;
}

static GF_TextSample* create_text_sample() {
    // Allocate a dummy buffer for GF_TextSample as we don't have its full definition
    GF_TextSample *text_sample = (GF_TextSample *)malloc(1); // Allocate minimal memory
    return text_sample;
}

int LLVMFuzzerTestOneInput_218(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + sizeof(u64) + sizeof(u8) + sizeof(u16)) return 0;

    GF_ISOSample *sample = create_sample();
    GF_ISOFile *iso_file = create_iso_file();
    GF_TextSample *text_sample = create_text_sample();
    if (!sample || !iso_file || !text_sample) {
        free(sample);
        free(iso_file);
        free(text_sample);
        return 0;
    }

    u32 trackNumber = *(u32 *)Data;
    u32 sampleDescriptionIndex = *(u32 *)(Data + sizeof(u32));
    u64 dataOffset = *(u64 *)(Data + 2 * sizeof(u32));

    // Fuzz gf_isom_add_sample
    gf_isom_add_sample(iso_file, trackNumber, sampleDescriptionIndex, sample);

    // Fuzz gf_isom_sample_del
    gf_isom_sample_del(&sample);

    // Fuzz gf_isom_get_track_template
    u8 *output = NULL;
    u32 output_size = 0;
    gf_isom_get_track_template(iso_file, trackNumber, &output, &output_size);
    free(output);

    // Fuzz gf_isom_add_sample_reference
    gf_isom_add_sample_reference(iso_file, trackNumber, sampleDescriptionIndex, sample, dataOffset);

    // Fuzz gf_isom_fragment_add_sample
    u32 Duration = *(u32 *)(Data + 3 * sizeof(u32));
    u8 PaddingBits = *(u8 *)(Data + 4 * sizeof(u32));
    u16 DegradationPriority = *(u16 *)(Data + 4 * sizeof(u32) + sizeof(u8));
    Bool redundantCoding = *(Bool *)(Data + 4 * sizeof(u32) + sizeof(u8) + sizeof(u16));
    gf_isom_fragment_add_sample(iso_file, trackNumber, sample, sampleDescriptionIndex, Duration, PaddingBits, DegradationPriority, redundantCoding);

    // Fuzz gf_isom_text_to_sample
    GF_ISOSample *iso_sample = gf_isom_text_to_sample(text_sample);
    free(iso_sample);

    free(iso_file);
    free(text_sample);
    return 0;
}