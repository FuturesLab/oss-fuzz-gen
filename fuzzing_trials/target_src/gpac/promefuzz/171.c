// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open_progressive_ex at isom_read.c:435:8 in isomedia.h
// gf_isom_get_omadrm_info at drm_sample.c:296:8 in isomedia.h
// gf_isom_set_movie_duration at movie_fragments.c:61:8 in isomedia.h
// gf_isom_get_sidx_duration at isom_read.c:6196:8 in isomedia.h
// gf_isom_set_fragment_reference_time at movie_fragments.c:2552:8 in isomedia.h
// gf_isom_reset_data_offset at isom_read.c:3151:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_171(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    write_dummy_file(Data, Size);

    GF_ISOFile *isom_file = NULL;
    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 1;
    u32 outOriginalFormat = 0;
    u32 outSchemeType = 0;
    u32 outSchemeVersion = 0;
    const char *outContentID = NULL;
    const char *outRightsIssuerURL = NULL;
    const char *outTextualHeaders = NULL;
    u32 outTextualHeadersLen = 0;
    u64 outPlaintextLength = 0;
    u32 outEncryptionType = 0;
    Bool outSelectiveEncryption = 0;
    u32 outIVLength = 0;
    u32 outKeyIndicationLength = 0;

    gf_isom_open_progressive_ex("./dummy_file", 0, Size, 0, &isom_file, NULL, NULL);

    gf_isom_get_omadrm_info(
        isom_file, trackNumber, sampleDescriptionIndex,
        &outOriginalFormat, &outSchemeType, &outSchemeVersion,
        &outContentID, &outRightsIssuerURL, &outTextualHeaders, &outTextualHeadersLen,
        &outPlaintextLength, &outEncryptionType, &outSelectiveEncryption,
        &outIVLength, &outKeyIndicationLength
    );

    u64 duration = 1000;
    Bool remove_mehd = 1;

    gf_isom_set_movie_duration(isom_file, duration, remove_mehd);

    u64 sidx_dur = 0;
    u32 sidx_timescale = 0;

    gf_isom_get_sidx_duration(isom_file, &sidx_dur, &sidx_timescale);

    GF_ISOTrackID reference_track_ID = 1;
    u64 ntp = 0;
    u64 timestamp = 0;
    Bool at_mux = 0;

    gf_isom_set_fragment_reference_time(isom_file, reference_track_ID, ntp, timestamp, at_mux);

    u64 top_box_start = 0;
    gf_isom_reset_data_offset(isom_file, &top_box_start);

    if (isom_file) {
        // Assuming a function to close and free GF_ISOFile, e.g., gf_isom_close(isom_file);
    }

    return 0;
}