#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *vfs_name = (char *)malloc(size + 1);
    if (vfs_name == NULL) {
        return 0;
    }

    // Copy the data into the string and null-terminate it
    memcpy(vfs_name, data, size);
    vfs_name[size] = '\0';

    // Call the function-under-test
    sqlite3_vfs *vfs = sqlite3_vfs_find(vfs_name);

    // Free the allocated memory
    free(vfs_name);

    return 0;
}