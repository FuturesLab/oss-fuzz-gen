#include <stdint.h>
#include <stddef.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_199(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    GF_ISOFile *movie;
    u32 trackNumber;
    u64 EditDuration;
    u64 MediaTime;
    GF_ISOEditType EditMode;

    // Ensure size is sufficient to extract parameters
    if (size < sizeof(u32) + 2 * sizeof(u64) + sizeof(GF_ISOEditType)) {
        return 0;
    }

    // Initialize the movie object (assuming a valid movie object is created here)
    movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract parameters from the input data
    trackNumber = *((u32*)data);
    EditDuration = *((u64*)(data + sizeof(u32)));
    MediaTime = *((u64*)(data + sizeof(u32) + sizeof(u64)));
    EditMode = *((GF_ISOEditType*)(data + sizeof(u32) + 2 * sizeof(u64)));

    // Call the function-under-test
    gf_isom_append_edit(movie, trackNumber, EditDuration, MediaTime, EditMode);

    // Close and clean up the movie object
    gf_isom_close(movie);

    return 0;
}