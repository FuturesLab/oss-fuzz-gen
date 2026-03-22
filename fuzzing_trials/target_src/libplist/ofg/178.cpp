#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    // Initialize plist_t with some data
    plist_t plist = plist_new_data((const char *)data, (uint32_t)size);

    // Initialize output parameters
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