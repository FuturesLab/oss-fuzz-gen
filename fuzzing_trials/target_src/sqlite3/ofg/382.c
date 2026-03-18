#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_382(const uint8_t *data, size_t size) {
    // Ensure size is not zero to avoid passing 0 to sqlite3_malloc
    if (size == 0) {
        return 0;
    }

    // Use the size as the input to sqlite3_malloc
    // Limit the allocation size to a reasonable value to avoid excessive memory usage
    int alloc_size = size > 1024 ? 1024 : (int)size;

    // Call the function-under-test
    void *ptr = sqlite3_malloc(alloc_size);

    // If allocation was successful, free the memory
    if (ptr != NULL) {
        sqlite3_free(ptr);
    }

    return 0;
}