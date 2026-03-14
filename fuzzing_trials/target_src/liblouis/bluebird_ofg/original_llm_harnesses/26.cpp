#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" {
    // Include the correct header file where lou_getTable is declared
    #include "/src/liblouis/liblouis/liblouis.h"
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C-style string
    char *tableName = (char *)malloc(size + 1);
    if (tableName == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(tableName, data, size);
    tableName[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    const void *result = lou_getTable(tableName);

    // Free the allocated memory
    free(tableName);

    // Return 0 to indicate successful execution
    return 0;
}