#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Ensure data is null-terminated for XML parsing
    char *xml_data = (char *)malloc(size + 1);
    if (xml_data == NULL) {
        return 0;
    }
    memcpy(xml_data, data, size);
    xml_data[size] = '\0';

    // Initialize plist_t
    plist_t plist = NULL;

    // Call the function-under-test
    plist_err_t result = plist_from_xml(xml_data, (uint32_t)size, &plist);

    // Clean up
    if (plist != NULL) {
        plist_free(plist);
    }
    free(xml_data);

    return 0;
}