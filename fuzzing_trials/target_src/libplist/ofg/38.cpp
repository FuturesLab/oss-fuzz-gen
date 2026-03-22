extern "C" {
#include <plist/plist.h>
}

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Ensure the size is enough to create a non-empty string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *input_string = new char[size + 1];
    memcpy(input_string, data, size);
    input_string[size] = '\0';

    // Check if the input string is not empty
    if (strlen(input_string) == 0) {
        delete[] input_string;
        return 0;
    }

    // Create a plist node of type PLIST_STRING using the input data
    plist_t plist = plist_new_string(input_string);

    // Ensure the plist node was created successfully
    if (plist != NULL) {
        // Call the function-under-test with a valid plist and input string
        plist_string_val_contains(plist, input_string);

        // Clean up
        plist_free(plist);
    }

    delete[] input_string;

    return 0;
}