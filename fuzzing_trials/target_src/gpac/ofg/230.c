#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h> // Include the necessary header for GF_ISOFile and related types

extern int LLVMFuzzerTestOneInput_230(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract parameters
    if (size < sizeof(GF_ISOTrackID) + 3 * sizeof(u32) + 2 * sizeof(u8) + sizeof(u16) + sizeof(Bool)) {
        return 0;
    }

    // Initialize the variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL); // Open a dummy ISO file
    if (!movie) {
        return 0;
    }

    GF_ISOTrackID TrackID = *((GF_ISOTrackID *)data);
    data += sizeof(GF_ISOTrackID);

    u32 DefaultSampleDescriptionIndex = *((u32 *)data);
    data += sizeof(u32);

    u32 DefaultSampleDuration = *((u32 *)data);
    data += sizeof(u32);

    u32 DefaultSampleSize = *((u32 *)data);
    data += sizeof(u32);

    u8 DefaultSampleSyncFlags = *data;
    data += sizeof(u8);

    u8 DefaultSamplePadding = *data;
    data += sizeof(u8);

    u16 DefaultDegradationPriority = *((u16 *)data);
    data += sizeof(u16);

    Bool force_traf_flags = *((Bool *)data);

    // Call the function-under-test
    gf_isom_setup_track_fragment(movie, TrackID, DefaultSampleDescriptionIndex,
                                 DefaultSampleDuration, DefaultSampleSize,
                                 DefaultSampleSyncFlags, DefaultSamplePadding,
                                 DefaultDegradationPriority, force_traf_flags);

    // Clean up
    gf_isom_close(movie);

    return 0;
}