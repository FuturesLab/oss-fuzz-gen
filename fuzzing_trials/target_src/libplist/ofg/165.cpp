#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a plist
    if (size < 1) {
        return 0;
    }

    // Create a plist node
    plist_t node = plist_new_data((const char *)data, (uint32_t)size);

    // Check if the node is created successfully
    if (node) {
        // Use the plist node in a meaningful way to increase code coverage
        char *xml = NULL;
        uint32_t length = 0;
        plist_to_xml(node, &xml, &length);

        // Free the allocated XML buffer
        if (xml) {
            free(xml);
        }

        // Free the plist node
        plist_free(node);
    }

    return 0;
}