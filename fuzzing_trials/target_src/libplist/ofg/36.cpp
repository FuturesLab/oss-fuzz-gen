#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    plist_t plist = NULL;
    char *json_output = NULL;
    uint32_t json_length = 0;
    int format = 0;

    // Create a plist from the input data
    plist_format_t plist_format = PLIST_FORMAT_BINARY; // Use a valid plist format

    plist_from_memory((const char *)data, size, &plist, &plist_format);

    if (plist != NULL) {
        // Call the function-under-test
        plist_err_t err = plist_to_json(plist, &json_output, &json_length, format);

        // Free the allocated JSON output if it was created
        if (json_output != NULL) {
            free(json_output);
        }

        // Free the plist
        plist_free(plist);
    }

    return 0;
}