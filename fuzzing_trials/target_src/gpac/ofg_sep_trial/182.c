#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for all parameters
    if (size < sizeof(u32) + 3 * sizeof(u64) + sizeof(GF_ISOEditType)) {
        return 0;
    }

    // Initialize the movie object
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract parameters from the input data
    u32 trackNumber = *(u32 *)data;
    data += sizeof(u32);
    
    u64 EditTime = *(u64 *)data;
    data += sizeof(u64);
    
    u64 EditDuration = *(u64 *)data;
    data += sizeof(u64);
    
    u64 MediaTime = *(u64 *)data;
    data += sizeof(u64);
    
    GF_ISOEditType EditMode = *(GF_ISOEditType *)data;

    // Call the function-under-test
    gf_isom_set_edit(movie, trackNumber, EditTime, EditDuration, MediaTime, EditMode);

    // Close the movie object
    gf_isom_close(movie);

    return 0;
}