#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

// Define the function without using extern "C"
int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for all parameters
    if (size < sizeof(uint32_t) + 3 * sizeof(uint64_t) + sizeof(GF_ISOEditType)) {
        return 0;
    }

    // Initialize a GF_ISOFile object
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract parameters from the input data
    uint32_t trackNumber = *((uint32_t *)data);
    data += sizeof(uint32_t);

    uint64_t EditTime = *((uint64_t *)data);
    data += sizeof(uint64_t);

    uint64_t EditDuration = *((uint64_t *)data);
    data += sizeof(uint64_t);

    uint64_t MediaTime = *((uint64_t *)data);
    data += sizeof(uint64_t);

    GF_ISOEditType EditMode = *((GF_ISOEditType *)data);

    // Call the function-under-test
    gf_isom_set_edit(movie, trackNumber, EditTime, EditDuration, MediaTime, EditMode);

    // Clean up
    gf_isom_close(movie);

    return 0;
}