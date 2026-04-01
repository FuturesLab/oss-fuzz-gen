#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <magic.h>

extern "C" {
    #include <magic.h>
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Initialize a magic_set
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0;
    }

    // Ensure that the data is null-terminated
    char *file_path = (char *)malloc(size + 1);
    if (file_path == NULL) {
        magic_close(magic);
        return 0;
    }
    memcpy(file_path, data, size);
    file_path[size] = '\0';

    // Call the function-under-test
    int result = magic_load(magic, file_path);

    // Clean up
    free(file_path);
    magic_close(magic);

    return result;
}