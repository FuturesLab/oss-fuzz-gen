// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_get_media_data_size at isom_read.c:4131:5 in isomedia.h
// gf_isom_get_missing_bytes at isom_read.c:2482:5 in isomedia.h
// gf_isom_get_current_tfdt at isom_read.c:5822:5 in isomedia.h
// gf_isom_get_track_duration at isom_read.c:1076:5 in isomedia.h
// gf_isom_get_track_magic at isom_read.c:6160:5 in isomedia.h
// gf_isom_get_media_original_duration at isom_read.c:1448:5 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32)) return 0;

    // Allocate memory for a dummy GF_ISOFile structure based on a reasonable assumption of size
    size_t isoFileSize = 1024; // Assume a size for the structure
    GF_ISOFile *isom_file = (GF_ISOFile *)malloc(isoFileSize);
    if (!isom_file) return 0; // Handle allocation failure

    // Initialize the allocated memory to ensure no garbage values
    memset(isom_file, 0, isoFileSize);

    // Use a portion of the input data to determine the track number
    u32 trackNumber = *((u32 *)Data);

    // Call each target function with the initialized data
    u64 media_data_size = gf_isom_get_media_data_size(isom_file, trackNumber);
    u64 missing_bytes = gf_isom_get_missing_bytes(isom_file, trackNumber);
    u64 current_tfdt = gf_isom_get_current_tfdt(isom_file, trackNumber);
    u64 track_duration = gf_isom_get_track_duration(isom_file, trackNumber);
    u64 track_magic = gf_isom_get_track_magic(isom_file, trackNumber);
    u64 media_original_duration = gf_isom_get_media_original_duration(isom_file, trackNumber);

    // Use the results to prevent the compiler from optimizing the calls away
    volatile u64 sink = media_data_size + missing_bytes + current_tfdt + track_duration + track_magic + media_original_duration;

    // Clean up
    free(isom_file);

    return 0;
}