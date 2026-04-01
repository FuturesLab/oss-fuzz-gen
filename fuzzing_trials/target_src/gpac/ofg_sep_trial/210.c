#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_210(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for extracting multiple u32 values
    if (size < sizeof(uint32_t) * 5) {
        return 0;
    }

    // Create a dummy GF_ISOFile object
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Extract u32 values from the input data
    uint32_t track = *(const uint32_t *)(data);
    uint32_t sample_number = *(const uint32_t *)(data + sizeof(uint32_t));
    uint32_t grouping_type = *(const uint32_t *)(data + 2 * sizeof(uint32_t));
    uint32_t sampleGroupDescriptionIndex = *(const uint32_t *)(data + 3 * sizeof(uint32_t));
    uint32_t grouping_type_parameter = *(const uint32_t *)(data + 4 * sizeof(uint32_t));

    // Call the function-under-test
    gf_isom_add_sample_info(movie, track, sample_number, grouping_type, sampleGroupDescriptionIndex, grouping_type_parameter);

    // Clean up
    gf_isom_close(movie);

    return 0;
}