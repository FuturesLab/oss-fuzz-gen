#include <stddef.h>
#include <stdint.h>
#include "/src/hoextdown/src/document.h"
#include "/src/hoextdown/src/hash.h"  // Include the header for hoedown_hash functions

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to call hoedown_hash_new with a valid size
    if (size == 0) {
        return 0;
    }

    // Use the size of the input data as the parameter for hoedown_hash_new
    hoedown_hash *hash = hoedown_hash_new(size);

    // Free the allocated hash if it was successfully created
    if (hash != NULL) {
        hoedown_hash_free(hash);
    }

    return 0;
}