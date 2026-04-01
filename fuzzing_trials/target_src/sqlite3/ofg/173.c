#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h> // Include stdlib.h for malloc and free

int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and not empty
    if (size == 0) {
        return 0;
    }

    // Create a buffer to hold the null-terminated string
    char *vfs_name = (char *)malloc(size + 1);
    if (vfs_name == NULL) {
        return 0;
    }

    // Copy data into the buffer and null-terminate it
    memcpy(vfs_name, data, size);
    vfs_name[size] = '\0';

    // Call the function-under-test
    sqlite3_vfs *vfs = sqlite3_vfs_find(vfs_name);

    // Clean up
    free(vfs_name);

    return 0;
}