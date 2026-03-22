#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    plist_err_t plist_from_memory(const char *, uint32_t, plist_t *, plist_format_t *);
}

extern "C" int LLVMFuzzerTestOneInput_163(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input string, ensuring it is null-terminated
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Initialize the plist and format variables
    plist_t plist = NULL;
    plist_format_t format = PLIST_FORMAT_XML;

    // Call the function-under-test
    plist_err_t result = plist_from_memory(input, (uint32_t)size, &plist, &format);

    // Clean up
    if (plist != NULL) {
        plist_free(plist);
    }
    free(input);

    return 0;
}