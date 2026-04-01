extern "C" {
    #include <plist/plist.h>
}

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputString = new char[size + 1];
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Initialize a plist node from the input data
    plist_t node1 = plist_new_string(inputString);

    // Initialize another plist node with a constant string for comparison
    plist_t node2 = plist_new_string("test");

    // Call the function-under-test
    int result = plist_string_val_compare(node1, inputString);

    // Clean up
    plist_free(node1);
    plist_free(node2);
    delete[] inputString;

    return 0;
}