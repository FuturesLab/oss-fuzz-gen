// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_get_omadrm_info at drm_sample.c:296:8 in isomedia.h
// gf_isom_set_media_creation_time at isom_write.c:242:8 in isomedia.h
// gf_isom_get_last_producer_time_box at isom_read.c:5800:6 in isomedia.h
// gf_isom_close_segment at movie_fragments.c:1743:8 in isomedia.h
// gf_isom_get_media_time at isom_read.c:1342:8 in isomedia.h
// gf_isom_set_fragment_reference_time at movie_fragments.c:2552:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy ISO file structure
    GF_ISOFile *iso = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso;
}

static void cleanup_iso_file(GF_ISOFile *iso) {
    // Cleanup the dummy ISO file structure
    if (iso) {
        gf_isom_close(iso);
    }
}

int LLVMFuzzerTestOneInput_275(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 2) return 0;

    // Create a dummy ISO file
    GF_ISOFile *iso = create_dummy_iso_file();
    if (!iso) return 0;

    // Prepare parameters for gf_isom_get_omadrm_info
    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + 4));
    u32 outOriginalFormat, outSchemeType, outSchemeVersion;
    const char *outContentID, *outRightsIssuerURL, *outTextualHeaders;
    u32 outTextualHeadersLen;
    u64 outPlaintextLength;
    u32 outEncryptionType;
    Bool outSelectiveEncryption;
    u32 outIVLength, outKeyIndicationLength;

    gf_isom_get_omadrm_info(iso, trackNumber, sampleDescriptionIndex, &outOriginalFormat, &outSchemeType, &outSchemeVersion,
                            &outContentID, &outRightsIssuerURL, &outTextualHeaders, &outTextualHeadersLen, &outPlaintextLength, &outEncryptionType,
                            &outSelectiveEncryption, &outIVLength, &outKeyIndicationLength);

    // Prepare parameters for gf_isom_set_media_creation_time
    u64 create_time = *((u64 *)(Data + 8));
    u64 modif_time = *((u64 *)(Data + 16));

    gf_isom_set_media_creation_time(iso, trackNumber, create_time, modif_time);

    // Prepare parameters for gf_isom_get_last_producer_time_box
    GF_ISOTrackID refTrackID;
    u64 ntp, timestamp;
    Bool reset_info = GF_TRUE;

    gf_isom_get_last_producer_time_box(iso, &refTrackID, &ntp, &timestamp, reset_info);

    // Prepare parameters for gf_isom_close_segment
    s32 subsegs_per_sidx = *((s32 *)(Data + 24));
    GF_ISOTrackID referenceTrackID = *((u32 *)(Data + 28));
    u64 ref_track_decode_time = *((u64 *)(Data + 32));
    s32 timestamp_shift = *((s32 *)(Data + 40));
    u64 ref_track_next_cts = *((u64 *)(Data + 44));
    Bool daisy_chain_sidx = GF_FALSE;
    Bool use_ssix = GF_FALSE;
    Bool last_segment = GF_FALSE;
    Bool close_segment_handle = GF_FALSE;
    u32 segment_marker_4cc = *((u32 *)(Data + 52));
    u64 index_start_range, index_end_range, out_seg_size;

    gf_isom_close_segment(iso, subsegs_per_sidx, referenceTrackID, ref_track_decode_time, timestamp_shift, ref_track_next_cts,
                          daisy_chain_sidx, use_ssix, last_segment, close_segment_handle, segment_marker_4cc,
                          &index_start_range, &index_end_range, &out_seg_size);

    // Prepare parameters for gf_isom_get_media_time
    u32 movieTime = *((u32 *)(Data + 56));
    u64 mediaTime;

    gf_isom_get_media_time(iso, trackNumber, movieTime, &mediaTime);

    // Prepare parameters for gf_isom_set_fragment_reference_time
    GF_ISOTrackID reference_track_ID = *((u32 *)(Data + 60));
    u64 ntp_time = *((u64 *)(Data + 64));
    u64 media_timestamp = *((u64 *)(Data + 72));
    Bool at_mux = GF_FALSE;

    gf_isom_set_fragment_reference_time(iso, reference_track_ID, ntp_time, media_timestamp, at_mux);

    // Cleanup
    cleanup_iso_file(iso);

    return 0;
}