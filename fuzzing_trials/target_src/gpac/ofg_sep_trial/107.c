#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 track = 1; // Assuming track 1 for simplicity
    u32 grouping_type = 1; // Arbitrary grouping type
    void *group_data = NULL;
    u32 data_size = size;
    Bool is_default = GF_FALSE;
    u32 sampleGroupDescriptionIndex = 0;

    // Ensure movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Allocate memory for data
    group_data = malloc(data_size);
    if (group_data == NULL) {
        gf_isom_close(movie);
        return 0;
    }

    // Copy data into group_data
    memcpy(group_data, data, data_size);

    // Call the function-under-test
    gf_isom_add_sample_group_info(movie, track, grouping_type, group_data, data_size, is_default, &sampleGroupDescriptionIndex);

    // Clean up
    free(group_data);
    gf_isom_close(movie);

    return 0;
}