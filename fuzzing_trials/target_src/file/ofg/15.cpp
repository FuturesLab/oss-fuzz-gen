extern "C" {
    #include <magic.h>
    #include <stdint.h>
    #include <stdlib.h>
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Initialize a magic_set structure
    struct magic_set *magic = magic_open(MAGIC_NONE);

    // Check if magic_open was successful
    if (magic == NULL) {
        return 0;
    }

    // Load default magic database
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        return 0;
    }

    // Call the function-under-test
    int result = magic_errno(magic);

    // Clean up
    magic_close(magic);

    return 0;
}