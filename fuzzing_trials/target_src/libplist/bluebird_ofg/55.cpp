extern "C" {
#include "plist/plist.h"
}

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a non-empty string
    if (size == 0) {
        return 0;
    }

    // Create a plist node of string type
    plist_t node = plist_new_string("initial");

    // Create a null-terminated string from the input data
    char *inputString = new char[size + 1];
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    plist_set_string_val(node, inputString);

    // Clean up
    plist_free(node);
    delete[] inputString;

    return 0;
}