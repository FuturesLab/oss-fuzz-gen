#include <cstdint>  // Include the header for uint8_t
#include <cstddef>  // Include the header for size_t
#include <iostream> // Include for output

extern "C" {
    #include <magic.h>
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    int flags = MAGIC_NONE;

    // Call the function-under-test
    magic_t magic_cookie = magic_open(flags);

    // Check if magic_open returned a valid magic cookie
    if (magic_cookie != nullptr) {
        // Load the default magic database
        if (magic_load(magic_cookie, NULL) == 0) {
            // Use magic_buffer to identify the type of the data
            const char *result = magic_buffer(magic_cookie, data, size);
            if (result != nullptr) {
                // Output the result for debugging purposes
                std::cout << "Identified data type: " << result << std::endl;
            }
        } else {
            // Output error if magic_load fails
            std::cerr << "Failed to load magic database: " << magic_error(magic_cookie) << std::endl;
        }

        // Close the magic cookie after use
        magic_close(magic_cookie);
    } else {
        // Output error if magic_open fails
        std::cerr << "Failed to open magic cookie." << std::endl;
    }

    return 0;
}