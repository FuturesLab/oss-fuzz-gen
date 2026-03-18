#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *movie = gf_isom_open("/dev/null", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0; // Early return if the movie cannot be opened
    }

    // Ensure that the input data is large enough to extract meaningful values
    if (size < sizeof(u32) * 4) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract values from the input data
    u32 trackNumber = *((u32 *)data);
    u32 trackRefGroup = *((u32 *)(data + sizeof(u32)));
    Bool is_switch_group = (Bool)(data[2 * sizeof(u32)] % 2); // Randomly choose between GF_TRUE or GF_FALSE
    u32 switchGroupID = *((u32 *)(data + 3 * sizeof(u32)));
    u32 criteriaListCount = 1;

    // Ensure the criteriaList is not NULL and has at least one element
    u32 criteriaList[1] = {0};

    // Call the function-under-test
    gf_isom_set_track_switch_parameter(movie, trackNumber, trackRefGroup, is_switch_group, &switchGroupID, criteriaList, criteriaListCount);

    // Clean up
    gf_isom_close(movie);

    return 0;
}