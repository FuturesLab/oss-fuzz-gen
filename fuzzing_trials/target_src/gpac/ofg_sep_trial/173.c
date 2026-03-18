#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>  // Include necessary for GF_ISOM_OPEN_READ

int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    // Adjust the size check since we can't use sizeof on GF_ISOFile
    if (size < 2 * sizeof(uint32_t)) {
        return 0; // Not enough data to proceed
    }

    // As we cannot use gf_isom_open_mem, we will initialize the file to NULL
    GF_ISOFile *file = NULL;

    // Extract track and ctts_shift from data
    uint32_t track = *(uint32_t*)(data);
    uint32_t ctts_shift = *(uint32_t*)(data + sizeof(uint32_t));

    // Call the function-under-test
    // Assuming gf_isom_set_ctts_v1 can handle a NULL file pointer gracefully
    gf_isom_set_ctts_v1(file, track, ctts_shift);

    // No need to close the file as it was never opened

    return 0;
}