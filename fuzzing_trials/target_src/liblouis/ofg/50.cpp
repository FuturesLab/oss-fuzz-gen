#include <cstdint>
#include <cstddef>
#include <cstdlib>

extern "C" {
    // Function-under-test declaration
    void lou_indexTables(const char **);
}

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Ensure size is large enough to create a meaningful input
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the input array of strings
    const char **tableNames = static_cast<const char **>(malloc(2 * sizeof(char *)));
    if (tableNames == NULL) {
        return 0; // Allocation failed, exit early
    }

    // Allocate memory for each string
    char *firstTable = static_cast<char *>(malloc(size + 1));
    char *secondTable = static_cast<char *>(malloc(size + 1));
    if (firstTable == NULL || secondTable == NULL) {
        free(tableNames);
        free(firstTable);
        free(secondTable);
        return 0; // Allocation failed, exit early
    }

    // Copy data into the strings and null-terminate them
    for (size_t i = 0; i < size; ++i) {
        firstTable[i] = static_cast<char>(data[i]);
        secondTable[i] = static_cast<char>(data[size - i - 1]);
    }
    firstTable[size] = '\0';
    secondTable[size] = '\0';

    // Assign strings to the array
    tableNames[0] = firstTable;
    tableNames[1] = secondTable;

    // Call the function under test
    lou_indexTables(tableNames);

    // Clean up allocated memory
    free(firstTable);
    free(secondTable);
    free(tableNames);

    return 0;
}