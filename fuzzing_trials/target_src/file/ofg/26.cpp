#include <cstdint>  // Include for uint8_t
#include <cstdlib>  // Include for malloc and free
#include <cstring>  // Include for memcpy

extern "C" {
    #include <magic.h>
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Initialize the magic_set structure
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated before using it as a string
    char *file_path = (char *)malloc(size + 1);
    if (file_path == NULL) {
        magic_close(magic);
        return 0;
    }
    memcpy(file_path, data, size);
    file_path[size] = '\0';

    // Call the function-under-test
    magic_load(magic, file_path);

    // Clean up
    free(file_path);
    magic_close(magic);

    return 0;
}