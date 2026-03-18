#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for size_t
#include <iostream> // Include for std::cerr

extern "C" {
    #include <magic.h>
    #include <stdlib.h>
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Check if the input data is valid
    if (data == nullptr || size == 0) {
        return 0;
    }

    // Initialize a magic_set structure
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        std::cerr << "Failed to initialize magic_set" << std::endl;
        return 0;
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        std::cerr << "Failed to load magic database: " << magic_error(magic) << std::endl;
        magic_close(magic);
        return 0;
    }

    // Use the data as input for magic_buffer
    const char *magic_result = magic_buffer(magic, data, size);
    if (magic_result == NULL) {
        std::cerr << "magic_buffer failed: " << magic_error(magic) << std::endl;
    } else {
        // Optionally, print the result to verify the function is working
        std::cout << "Magic buffer result: " << magic_result << std::endl;
    }

    // Clean up
    magic_close(magic);

    return 0;
}