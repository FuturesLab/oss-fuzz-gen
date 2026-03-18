#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include string.h for memcpy
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_319(const uint8_t *data, size_t size) {
    // Allocate memory to be freed by sqlite3_free
    void *ptr = sqlite3_malloc(size);
    
    // Copy the input data into the allocated memory if size is not zero
    if (size > 0 && ptr != NULL) {
        memcpy(ptr, data, size);
    }

    // Call the function-under-test
    sqlite3_free(ptr);

    return 0;
}