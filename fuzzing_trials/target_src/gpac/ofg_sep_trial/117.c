#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract necessary parameters
    if (size < sizeof(uint32_t) * 2 + sizeof(uint64_t)) {
        return 0;
    }

    // Initialize parameters for gf_isom_get_media_time
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!the_file) {
        return 0;
    }

    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t movieTime = *((uint32_t *)(data + sizeof(uint32_t)));
    uint64_t MediaTime = *((uint64_t *)(data + sizeof(uint32_t) * 2));

    // Call the function-under-test
    gf_isom_get_media_time(the_file, trackNumber, movieTime, &MediaTime);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}