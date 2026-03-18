#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" {
    // Assuming the function is defined in an external C library
    void lou_indexTables(const char **);
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Define a maximum number of strings to pass to the function
    const size_t maxStrings = 5;
    const char *stringArray[maxStrings + 1]; // +1 for the NULL terminator

    // Initialize all elements to NULL
    for (size_t i = 0; i < maxStrings + 1; ++i) {
        stringArray[i] = NULL;
    }

    // Create strings from the input data
    size_t offset = 0;
    for (size_t i = 0; i < maxStrings && offset < size; ++i) {
        // Find the length of the next string
        size_t len = 0;
        while (offset + len < size && data[offset + len] != '\0') {
            ++len;
        }

        // Allocate memory for the string and copy data
        char *str = new char[len + 1];
        std::memcpy(str, data + offset, len);
        str[len] = '\0'; // Null-terminate the string

        // Assign the string to the array
        stringArray[i] = str;

        // Move the offset past the current string
        offset += len + 1;
    }

    // Call the function with the array of strings
    lou_indexTables(stringArray);

    // Clean up allocated memory
    for (size_t i = 0; i < maxStrings; ++i) {
        delete[] stringArray[i];
    }

    return 0;
}