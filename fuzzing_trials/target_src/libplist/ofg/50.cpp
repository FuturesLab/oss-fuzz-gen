#include <stdint.h>
#include <stddef.h>
#include <plist/plist.h>
#include <stdlib.h>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the plist_t object
    plist_t plist = NULL;

    // Call the function-under-test
    plist_err_t result = plist_from_xml((const char *)data, (uint32_t)size, &plist);

    // Clean up plist if it was successfully created
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}