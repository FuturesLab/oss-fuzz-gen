#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for use as a C string
    char *vfs_name = (char *)malloc(size + 1);
    if (vfs_name == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data and null-terminate it
    memcpy(vfs_name, data, size);
    vfs_name[size] = '\0';

    // Call the function-under-test
    sqlite3_vfs *vfs = sqlite3_vfs_find(vfs_name);

    // Clean up
    free(vfs_name);

    return 0;
}