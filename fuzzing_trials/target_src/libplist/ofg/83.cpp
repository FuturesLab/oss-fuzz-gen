#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // Include for free function

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    if (data == NULL || size == 0) {
        return 0;
    }

    // Attempt to parse the input data as a plist
    plist_t plist = NULL;
    plist_from_bin(reinterpret_cast<const char *>(data), static_cast<uint32_t>(size), &plist);

    if (plist != NULL) {
        // Perform some operations on the plist to increase coverage
        char *xml = NULL;
        uint32_t length = 0;
        plist_to_xml(plist, &xml, &length);

        if (xml != NULL) {
            // Free the XML string
            free(xml);
        }

        // Clean up the plist object to prevent memory leaks
        plist_free(plist);
    }

    return 0;
}