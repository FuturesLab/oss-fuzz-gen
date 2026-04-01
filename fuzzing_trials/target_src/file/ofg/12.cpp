#include <cstddef>
#include <cstdint>
#include <cstring>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure the input size is not zero
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the file path string
    char *file_path = new char[size + 1];
    memcpy(file_path, data, size);
    file_path[size] = '\0'; // Null-terminate the string

    // Initialize a magic_set
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        delete[] file_path;
        return 0;
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        delete[] file_path;
        return 0;
    }

    // Call the function-under-test
    const char *result = magic_file(magic, file_path);

    // Clean up
    magic_close(magic);
    delete[] file_path;

    return 0;
}