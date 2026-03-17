// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open_progressive_ex at isom_read.c:435:8 in isomedia.h
// gf_isom_get_omadrm_info at drm_sample.c:296:8 in isomedia.h
// gf_isom_set_fragment_reference_time at movie_fragments.c:2552:8 in isomedia.h
// gf_isom_get_media_time at isom_read.c:1342:8 in isomedia.h
// gf_isom_refresh_size_info at stbl_write.c:2299:8 in isomedia.h
// gf_isom_close_segment at movie_fragments.c:1743:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3 + sizeof(u64) * 3) {
        return 0;
    }
    
    GF_ISOFile *isom_file = NULL;
    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    u32 reference_track_ID = *((u32 *)(Data + 2 * sizeof(u32)));
    u64 movieTime = *((u64 *)(Data + 3 * sizeof(u32)));
    u64 ntp = *((u64 *)(Data + 3 * sizeof(u32) + sizeof(u64)));
    u64 timestamp = *((u64 *)(Data + 3 * sizeof(u32) + 2 * sizeof(u64)));

    u32 outOriginalFormat, outSchemeType, outSchemeVersion, outTextualHeadersLen, outEncryptionType, outIVLength, outKeyIndicationLength;
    const char *outContentID, *outRightsIssuerURL, *outTextualHeaders;
    u64 outPlaintextLength;
    Bool outSelectiveEncryption;

    u64 mediaTime;
    u64 BytesMissing;
    u32 topBoxType;

    write_dummy_file(Data, Size);

    // Test gf_isom_open_progressive_ex
    gf_isom_open_progressive_ex("./dummy_file", 0, Size, 1, &isom_file, &BytesMissing, &topBoxType);

    if (isom_file) {
        // Test gf_isom_get_omadrm_info
        gf_isom_get_omadrm_info(isom_file, trackNumber, sampleDescriptionIndex, &outOriginalFormat, &outSchemeType, &outSchemeVersion,
            &outContentID, &outRightsIssuerURL, &outTextualHeaders, &outTextualHeadersLen, &outPlaintextLength, 
            &outEncryptionType, &outSelectiveEncryption, &outIVLength, &outKeyIndicationLength);
        
        // Test gf_isom_set_fragment_reference_time
        gf_isom_set_fragment_reference_time(isom_file, reference_track_ID, ntp, timestamp, 1);

        // Test gf_isom_get_media_time
        gf_isom_get_media_time(isom_file, trackNumber, movieTime, &mediaTime);

        // Test gf_isom_refresh_size_info
        gf_isom_refresh_size_info(isom_file, trackNumber);

        // Test gf_isom_close_segment
        gf_isom_close_segment(isom_file, 1, reference_track_ID, ntp, 0, timestamp, 1, 1, 1, 1, 0, NULL, NULL, NULL);

        // Clean up
        gf_isom_close(isom_file);
    }

    return 0;
}