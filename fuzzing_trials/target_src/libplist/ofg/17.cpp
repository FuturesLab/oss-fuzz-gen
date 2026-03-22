#include <cstdint>
#include <cstdlib>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Initialize plist_t object
    plist_t plist = nullptr;

    // Create a plist from the input data
    plist_from_bin((const char*)data, size, &plist);

    // If plist is not null, call the function-under-test
    if (plist != nullptr) {
        // Call the function-under-test
        uint32_t array_size = plist_array_get_size(plist);

        // Optionally, you can use the result to perform further operations
        // For this fuzzing harness, we're only interested in calling the function
        (void)array_size; // Suppress unused variable warning
    }

    // Free the plist object
    plist_free(plist);

    return 0;
}