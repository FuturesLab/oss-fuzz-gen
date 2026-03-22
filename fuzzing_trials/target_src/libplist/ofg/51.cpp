#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Ensure the input size is non-zero to create a valid plist_t object
    if (size == 0) {
        return 0;
    }

    // Convert the input data to a const char* to match the expected argument type
    const char* char_data = reinterpret_cast<const char*>(data);

    // Create a plist object from the input data
    plist_t plist = plist_new_data(char_data, size);

    // Call the function-under-test with the plist object, data, and size
    int result = plist_data_val_compare_with_size(plist, data, size);

    // Free the plist object to avoid memory leaks
    plist_free(plist);

    return 0;
}