// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_fragment_defaults at isom_read.c:2974:8 in isomedia.h
// gf_isom_change_track_fragment_defaults at movie_fragments.c:216:8 in isomedia.h
// gf_isom_end_hint_sample at hint_track.c:365:8 in isomedia.h
// gf_isom_fragment_add_sample at movie_fragments.c:2998:8 in isomedia.h
// gf_isom_get_sample_padding_bits at isom_read.c:2664:8 in isomedia.h
// gf_isom_rtp_packet_begin at hint_track.c:612:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy ISO file object with a temporary directory set to NULL
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_203(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    u32 defaultDuration = 0, defaultSize = 0, defaultDescriptionIndex = 0;
    u32 defaultRandomAccess = 0;
    u8 defaultPadding = 0;
    u16 defaultDegradationPriority = 0;

    // Fuzz gf_isom_get_fragment_defaults
    gf_isom_get_fragment_defaults(isom_file, trackNumber,
                                  &defaultDuration, &defaultSize, &defaultDescriptionIndex,
                                  &defaultRandomAccess, &defaultPadding, &defaultDegradationPriority);

    // Fuzz gf_isom_change_track_fragment_defaults
    gf_isom_change_track_fragment_defaults(isom_file, trackNumber,
                                           defaultDescriptionIndex, defaultDuration, defaultSize,
                                           defaultRandomAccess, defaultPadding, defaultDegradationPriority, 0);

    // Fuzz gf_isom_end_hint_sample
    gf_isom_end_hint_sample(isom_file, trackNumber, 0);

    // Fuzz gf_isom_fragment_add_sample
    GF_ISOSample sample;
    gf_isom_fragment_add_sample(isom_file, trackNumber, &sample, 0, defaultDuration, defaultPadding, defaultDegradationPriority, 0);

    // Fuzz gf_isom_get_sample_padding_bits
    u8 NbBits = 0;
    gf_isom_get_sample_padding_bits(isom_file, trackNumber, 1, &NbBits);

    // Fuzz gf_isom_rtp_packet_begin
    gf_isom_rtp_packet_begin(isom_file, trackNumber, 0, 0, 0, 0, 0, 0, 0, 0);

    cleanup_iso_file(isom_file);
    return 0;
}