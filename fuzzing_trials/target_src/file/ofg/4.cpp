#include <cstdint>
#include <cstdlib>
#include <string>
#include <cstring>

extern "C" {
#include "magic.h" // Assuming magic.h contains the declaration for magic_compile and magic_set
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to create a valid null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *magic_file = (char *)malloc(size + 1);
    if (magic_file == NULL) {
        return 0;
    }
    memcpy(magic_file, data, size);
    magic_file[size] = '\0';

    // Initialize a magic_set structure
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        free(magic_file);
        return 0;
    }

    // Call the function under test
    int result = magic_compile(magic, magic_file);

    // Clean up
    magic_close(magic);
    free(magic_file);

    return 0;
}