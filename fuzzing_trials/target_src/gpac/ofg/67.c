#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);

    if (!movie) {
        return 0;
    }

    // Ensure the size is large enough to extract meaningful values
    if (size < sizeof(uint32_t) * 5) {
        gf_isom_close(movie);
        return 0;
    }

    u32 track = *((u32*)data);
    u32 sample_number = *((u32*)(data + sizeof(u32)));
    u32 grouping_type = *((u32*)(data + 2 * sizeof(u32)));
    u32 grouping_type_parameter = *((u32*)(data + 3 * sizeof(u32)));
    u32 sgpd_flags = *((u32*)(data + 4 * sizeof(u32)));

    // Use remaining data as the sample group description data
    void *sample_group_data = (void*)(data + 5 * sizeof(u32));
    u32 data_size = size - 5 * sizeof(u32);

    // Call the function-under-test
    gf_isom_set_sample_group_description(movie, track, sample_number, grouping_type, grouping_type_parameter, sample_group_data, data_size, sgpd_flags);

    gf_isom_close(movie);
    return 0;
}