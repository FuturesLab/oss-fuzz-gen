// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_fragment_defaults at isom_read.c:2974:8 in isomedia.h
// gf_isom_fragment_add_sample at movie_fragments.c:2998:8 in isomedia.h
// gf_isom_change_track_fragment_defaults at movie_fragments.c:216:8 in isomedia.h
// gf_isom_end_hint_sample at hint_track.c:365:8 in isomedia.h
// gf_isom_get_sample_padding_bits at isom_read.c:2664:8 in isomedia.h
// gf_isom_rtp_packet_begin at hint_track.c:612:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile *create_dummy_iso_file() {
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
}

static void destroy_dummy_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) gf_isom_close(iso_file);
}

int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    u32 trackNumber = *(u32 *)Data;
    Data += sizeof(u32);
    Size -= sizeof(u32);

    u32 defaultDuration = 0, defaultSize = 0, defaultDescriptionIndex = 0, defaultRandomAccess = 0;
    u8 defaultPadding = 0;
    u16 defaultDegradationPriority = 0;

    gf_isom_get_fragment_defaults(iso_file, trackNumber, &defaultDuration, &defaultSize, &defaultDescriptionIndex,
                                  &defaultRandomAccess, &defaultPadding, &defaultDegradationPriority);

    if (Size < sizeof(GF_ISOSample)) {
        destroy_dummy_iso_file(iso_file);
        return 0;
    }

    GF_ISOSample *sample = (GF_ISOSample *)Data;
    Data += sizeof(GF_ISOSample);
    Size -= sizeof(GF_ISOSample);

    u32 sampleDescriptionIndex = 0;
    u32 Duration = 0;
    u8 PaddingBits = 0;
    u16 DegradationPriority = 0;
    Bool redundantCoding = 0;

    gf_isom_fragment_add_sample(iso_file, trackNumber, sample, sampleDescriptionIndex, Duration, PaddingBits, DegradationPriority, redundantCoding);

    u32 DefaultSampleDescriptionIndex = 0;
    u32 DefaultSampleDuration = 0;
    u32 DefaultSampleSize = 0;
    u8 DefaultSampleIsSync = 0;
    u8 DefaultSamplePadding = 0;
    u16 DefaultDegradationPriority = 0;
    u8 force_traf_flags = 0;

    gf_isom_change_track_fragment_defaults(iso_file, trackNumber, DefaultSampleDescriptionIndex, DefaultSampleDuration, DefaultSampleSize,
                                           DefaultSampleIsSync, DefaultSamplePadding, DefaultDegradationPriority, force_traf_flags);

    u8 IsRandomAccessPoint = 0;
    gf_isom_end_hint_sample(iso_file, trackNumber, IsRandomAccessPoint);

    u32 sampleNumber = 1;
    u8 NbBits = 0;
    gf_isom_get_sample_padding_bits(iso_file, trackNumber, sampleNumber, &NbBits);

    s32 relativeTime = 0;
    u8 PackingBit = 0;
    u8 eXtensionBit = 0;
    u8 MarkerBit = 0;
    u8 PayloadType = 0;
    u8 disposable_packet = 0;
    u8 IsRepeatedPacket = 0;
    u16 SequenceNumber = 0;

    gf_isom_rtp_packet_begin(iso_file, trackNumber, relativeTime, PackingBit, eXtensionBit, MarkerBit, PayloadType, disposable_packet, IsRepeatedPacket, SequenceNumber);

    destroy_dummy_iso_file(iso_file);
    return 0;
}