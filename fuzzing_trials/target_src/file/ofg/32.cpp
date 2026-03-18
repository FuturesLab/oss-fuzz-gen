extern "C" {
    #include <magic.h>
    #include <stddef.h>
    #include <stdint.h>
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    struct magic_set *magic;
    const char *result;

    // Initialize the magic_set structure
    magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0;
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        return 0;
    }

    // Call the function-under-test
    result = magic_buffer(magic, (const void *)data, size);

    // Handle the result if needed (here we just ensure it is called)
    if (result != NULL) {
        // You can perform additional checks or logging here
    }

    // Clean up
    magic_close(magic);

    return 0;
}