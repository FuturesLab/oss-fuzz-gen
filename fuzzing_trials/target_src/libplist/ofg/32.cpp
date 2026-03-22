#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    plist_err_t plist_to_openstep(plist_t plist, char **plist_xml, uint32_t *length, int format);
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a plist object from the input data
    plist_t plist = plist_new_data((const char *)data, size);
    if (!plist) {
        return 0;
    }

    // Initialize variables for the output parameters
    char *plist_xml = NULL;
    uint32_t length = 0;
    int format = 0;  // Assuming 0 is a valid format value, adjust as needed

    // Call the function-under-test
    plist_err_t err = plist_to_openstep(plist, &plist_xml, &length, format);

    // Free the plist object
    plist_free(plist);

    // If plist_to_openstep allocated memory for plist_xml, free it
    if (plist_xml) {
        free(plist_xml);
    }

    return 0;
}