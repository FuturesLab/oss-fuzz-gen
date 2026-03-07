#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>  // Include the necessary header for printf

extern "C" {
    #include <magic.h>  // Wrap the C library include with extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Initialize a magic_set
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        fprintf(stderr, "Failed to initialize magic library.\n");
        return 0;
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        fprintf(stderr, "Failed to load magic database: %s\n", magic_error(magic));
        magic_close(magic);
        return 0;
    }

    // Call the function-under-test
    const char *result = magic_buffer(magic, data, size);

    // Check the result
    if (result != NULL) {
        // Log the result to increase code coverage
        printf("Magic result: %s\n", result);
    } else {
        // Log the error if the result is NULL
        fprintf(stderr, "Magic buffer error: %s\n", magic_error(magic));
    }

    // Clean up
    magic_close(magic);

    return 0;
}