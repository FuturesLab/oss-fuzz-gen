#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // Include this for INT_MAX
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_338(const uint8_t *data, size_t size) {
    // Ensure the size is a positive integer for allocation
    int alloc_size = (size > 0 && size <= INT_MAX) ? (int)size : 1;

    // Call the function under test
    void *ptr = sqlite3_malloc(alloc_size);
    
    // Check if the allocation was successful
    if (ptr != NULL) {
        // Optionally, you can write to the allocated memory to further test
        memcpy(ptr, data, alloc_size > size ? size : alloc_size);
        
        // Free the allocated memory after use
        sqlite3_free(ptr);
    }

    return 0;
}