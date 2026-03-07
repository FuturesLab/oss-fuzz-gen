extern "C" {
    #include <magic.h>
    #include <stddef.h>
    #include <stdint.h>
}

#include <cstring> // Include the necessary header for memcpy

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Initialize variables
    struct magic_set *magic = NULL;
    const char *filename = NULL;

    // Ensure the size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the filename and ensure it's null-terminated
    char *fileBuffer = new char[size + 1];
    if (fileBuffer == NULL) {
        return 0;
    }
    memcpy(fileBuffer, data, size);
    fileBuffer[size] = '\0';  // Null-terminate the string
    filename = fileBuffer;

    // Create a magic set
    magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        delete[] fileBuffer;
        return 0;
    }

    // Call the function-under-test
    magic_compile(magic, filename);

    // Clean up
    magic_close(magic);
    delete[] fileBuffer;

    return 0;
}