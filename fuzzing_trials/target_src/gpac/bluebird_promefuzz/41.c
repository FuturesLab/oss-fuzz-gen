#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_iso_file() {
    // Create and initialize a new GF_ISOFile structure
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    // Close the ISO file and free any resources
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) {
        return 0; // Not enough data to proceed
    }

    // Create a dummy file to simulate the ISO file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    GF_ISOFile *isom_file = create_iso_file();
    if (!isom_file) {
        return 0;
    }

    // Prepare variables for gf_isom_get_omadrm_info
    u32 trackNumber = Data[0];
    u32 sampleDescriptionIndex = Data[1];
    u32 outOriginalFormat, outSchemeType, outSchemeVersion, outTextualHeadersLen, outEncryptionType, outIVLength, outKeyIndicationLength;
    const char *outContentID, *outRightsIssuerURL, *outTextualHeaders;
    u64 outPlaintextLength;
    Bool outSelectiveEncryption;

    // Call gf_isom_get_omadrm_info
    gf_isom_get_omadrm_info(isom_file, trackNumber, sampleDescriptionIndex, &outOriginalFormat, &outSchemeType, &outSchemeVersion,
                            &outContentID, &outRightsIssuerURL, &outTextualHeaders, &outTextualHeadersLen, &outPlaintextLength,
                            &outEncryptionType, &outSelectiveEncryption, &outIVLength, &outKeyIndicationLength);

    // Prepare variables for gf_isom_set_media_creation_time
    u64 create_time = (Size > 8) ? *(u64 *)(Data + 2) : 0;
    u64 modif_time = (Size > 16) ? *(u64 *)(Data + 10) : 0;

    // Call gf_isom_set_media_creation_time
    gf_isom_set_media_creation_time(isom_file, trackNumber, create_time, modif_time);

    // Prepare variables for gf_isom_get_last_producer_time_box
    GF_ISOTrackID refTrackID;
    u64 ntp, timestamp;
    Bool reset_info = Data[Size - 1] % 2;

    // Call gf_isom_get_last_producer_time_box
    gf_isom_get_last_producer_time_box(isom_file, &refTrackID, &ntp, &timestamp, reset_info);

    // Prepare variables for gf_isom_close_segment
    s32 subsegs_per_sidx = (Size > 20) ? *(s32 *)(Data + 18) : 0;
    GF_ISOTrackID referenceTrackID = trackNumber;
    u64 ref_track_decode_time = (Size > 28) ? *(u64 *)(Data + 22) : 0;
    s32 timestamp_shift = (Size > 32) ? *(s32 *)(Data + 30) : 0;
    u64 ref_track_next_cts = (Size > 40) ? *(u64 *)(Data + 34) : 0;
    Bool daisy_chain_sidx = Data[Size - 2] % 2;
    Bool use_ssix = Data[Size - 3] % 2;
    Bool last_segment = Data[Size - 4] % 2;
    Bool close_segment_handle = Data[Size - 5] % 2;
    u32 segment_marker_4cc = (Size > 44) ? *(u32 *)(Data + 42) : 0;
    u64 index_start_range, index_end_range, out_seg_size;

    // Call gf_isom_close_segment
    gf_isom_close_segment(isom_file, subsegs_per_sidx, referenceTrackID, ref_track_decode_time, timestamp_shift, ref_track_next_cts,
                          daisy_chain_sidx, use_ssix, last_segment, close_segment_handle, segment_marker_4cc,
                          &index_start_range, &index_end_range, &out_seg_size);

    // Prepare variables for gf_isom_get_media_time
    u32 movieTime = (Size > 48) ? *(u32 *)(Data + 46) : 0;
    u64 mediaTime;

    // Call gf_isom_get_media_time
    gf_isom_get_media_time(isom_file, trackNumber, movieTime, &mediaTime);

    // Prepare variables for gf_isom_set_fragment_reference_time
    GF_ISOTrackID reference_track_ID = trackNumber;
    u64 ntp_time = (Size > 56) ? *(u64 *)(Data + 50) : 0;
    u64 media_timestamp = (Size > 64) ? *(u64 *)(Data + 58) : 0;
    Bool at_mux = Data[Size - 6] % 2;

    // Call gf_isom_set_fragment_reference_time
    gf_isom_set_fragment_reference_time(isom_file, reference_track_ID, ntp_time, media_timestamp, at_mux);

    // Cleanup
    cleanup_iso_file(isom_file);

    return 0;
}