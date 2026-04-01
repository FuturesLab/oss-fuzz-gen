#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    // Initialize the plist
    plist_t plist = NULL;
    plist_format_t format = PLIST_FORMAT_XML; // Default format

    // The plist_from_memory function requires 4 arguments
    plist_from_memory((const char *)data, size, &plist, &format);

    if (plist == NULL) {
        return 0;
    }

    // Prepare variables for plist_to_xml
    char *xml = NULL;
    uint32_t xml_length = 0;

    // Call the function-under-test
    plist_err_t result = plist_to_xml(plist, &xml, &xml_length);

    // Clean up
    if (xml != NULL) {
        free(xml);
    }
    plist_free(plist);

    return 0;
}