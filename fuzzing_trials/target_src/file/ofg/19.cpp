#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    struct magic_set *magic;
    int descriptor;
    const char *result;

    // Initialize magic_set
    magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0;
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        return 0;
    }

    // Ensure the size is large enough to simulate a file descriptor
    if (size < sizeof(int)) {
        magic_close(magic);
        return 0;
    }

    // Use the data as a fake file descriptor
    memcpy(&descriptor, data, sizeof(int));

    // Call the function-under-test
    result = magic_descriptor(magic, descriptor);

    // Optionally, you can print the result for debugging purposes
    // printf("Magic descriptor result: %s\n", result);

    // Clean up
    magic_close(magic);

    return 0;
}