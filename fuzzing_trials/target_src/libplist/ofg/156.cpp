#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <plist/plist.h>

extern "C" {
    plist_err_t plist_from_openstep(const char *, uint32_t, plist_t *);
}

extern "C" int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *input_str = static_cast<char *>(malloc(size + 1));
    if (input_str == nullptr) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Initialize a plist_t variable
    plist_t plist = nullptr;

    // Call the function-under-test
    plist_err_t result = plist_from_openstep(input_str, static_cast<uint32_t>(size), &plist);

    // Clean up
    free(input_str);
    if (plist != nullptr) {
        plist_free(plist);
    }

    return 0;
}