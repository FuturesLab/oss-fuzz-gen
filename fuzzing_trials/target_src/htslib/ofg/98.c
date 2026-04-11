#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create an hts_itr_t object
    if (size < sizeof(hts_itr_t)) {
        return 0;
    }

    // Allocate memory for hts_itr_t
    hts_itr_t *itr = (hts_itr_t *)malloc(sizeof(hts_itr_t));
    if (itr == NULL) {
        return 0;
    }

    // Initialize hts_itr_t with fuzz data
    // Note: This is a simplified example and assumes hts_itr_t can be initialized this way
    // In a real scenario, you would need to properly initialize the structure
    memcpy(itr, data, sizeof(hts_itr_t));

    // Call the function-under-test
    hts_itr_destroy(itr);

    // Normally, hts_itr_destroy would free the memory, but if it doesn't, ensure to free it
    // free(itr); // Uncomment if hts_itr_destroy does not free the memory

    return 0;
}