extern "C" {
    #include "/src/libplist/libcnary/include/node.h"
    #include "plist/plist.h"
    #include <stdlib.h>  // Include for free function
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    int debug_level = 0;

    // Use the input data to set a debug level. 
    // Ensure that the debug level is within a reasonable range.
    if (size > 0) {
        debug_level = static_cast<int>(data[0] % 5); // Example: Modulo to limit debug level range from 0 to 4
    }

    // Call the function-under-test with the determined debug level
    plist_set_debug(debug_level);

    // Create a plist from the input data
    plist_t plist = nullptr;
    if (size > 0) {
        plist_from_bin(reinterpret_cast<const char*>(data), size, &plist);

        // Perform operations on the plist to increase code coverage
        if (plist != nullptr) {
            // Example operation: convert plist to XML and back
            char *xml = nullptr;
            uint32_t xml_size = 0;
            plist_to_xml(plist, &xml, &xml_size);
            if (xml) {
                plist_t new_plist = nullptr;
                plist_from_xml(xml, xml_size, &new_plist);
                plist_free(new_plist);
                free(xml);
            }
            plist_free(plist);
        }
    }

    return 0;
}