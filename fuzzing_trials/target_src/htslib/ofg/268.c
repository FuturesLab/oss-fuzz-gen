#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <htslib/tbx.h>  // Include the header that defines hts_idx_t

int LLVMFuzzerTestOneInput_268(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to extract necessary data
    if (size < sizeof(int) + 1) {
        return 0;
    }

    // Initialize a mock hts_idx_t object
    hts_idx_t *idx = tbx_index_load("dummy");  // Use a function to initialize a non-null idx

    if (idx == NULL) {
        return 0;  // Handle the case where index loading fails
    }

    // Extract an integer value from the input data
    int val;
    memcpy(&val, data, sizeof(int));

    // Ensure the string is null-terminated by allocating extra space
    size_t name_size = size - sizeof(int);
    char *name = (char *)malloc(name_size + 1);
    if (name == NULL) {
        tbx_destroy(idx);  // Clean up if malloc fails
        return 0;
    }
    memcpy(name, data + sizeof(int), name_size);
    name[name_size] = '\0'; // Null-terminate the string

    // Call the function-under-test with a non-null idx
    hts_idx_tbi_name(idx, val, name);

    // Clean up
    tbx_destroy(idx);  // Properly clean up the index object
    free(name);

    return 0;
}