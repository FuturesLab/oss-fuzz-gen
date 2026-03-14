#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/liblouis/liblouis/liblouis.h"
}

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create two non-empty strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for the two string arguments
    size_t mid = size / 2;

    // Create null-terminated strings from the input data
    char *tableName = static_cast<char*>(malloc(mid + 1));
    char *tableInfo = static_cast<char*>(malloc(size - mid + 1));

    if (tableName == nullptr || tableInfo == nullptr) {
        free(tableName);
        free(tableInfo);
        return 0;
    }

    memcpy(tableName, data, mid);
    tableName[mid] = '\0';

    memcpy(tableInfo, data + mid, size - mid);
    tableInfo[size - mid] = '\0';

    // Call the function under test
    char *result = lou_getTableInfo(tableName, tableInfo);

    // Free the result if it's not null
    if (result != nullptr) {
        free(result);
    }

    // Free the allocated memory
    free(tableName);
    free(tableInfo);

    return 0;
}