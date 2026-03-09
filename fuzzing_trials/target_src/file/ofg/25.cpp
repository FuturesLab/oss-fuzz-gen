#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <magic.h>

extern "C" {
    #include <magic.h>
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Initialize the magic set
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        magic_close(magic);
        return 0;
    }
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    int result = magic_load(magic, filename);

    // Clean up
    free(filename);
    magic_close(magic);

    return 0;
}