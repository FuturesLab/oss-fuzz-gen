#include <cstddef> // For size_t
#include <cstdint> // For uint8_t
#include <cstdlib> // For NULL

extern "C" {
    #include <magic.h>
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int flags = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    magic_t magic_cookie = magic_open(flags);

    // Check if magic_open was successful
    if (magic_cookie != NULL) {
        // Clean up by closing the magic cookie
        magic_close(magic_cookie);
    }

    return 0;
}