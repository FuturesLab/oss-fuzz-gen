#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for the function-under-test
    GF_ISOFile *movie = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL); // Open a test movie file
    if (!movie) return 0;

    u32 track = 1; // Assume a valid track ID
    u32 grouping_type = 1; // Some arbitrary grouping type
    void *data_ptr = (void *)data; // Use the input data as the data parameter
    u32 data_size = (u32)size; // Size of the input data
    Bool is_default = GF_FALSE; // Arbitrary choice of default flag
    u32 sampleGroupDescriptionIndex = 0; // Initialize the index

    // Call the function-under-test
    gf_isom_add_sample_group_info(movie, track, grouping_type, data_ptr, data_size, is_default, &sampleGroupDescriptionIndex);

    // Cleanup
    gf_isom_close(movie);

    return 0;
}