#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "dwarf.h"  // Assuming this header contains the declaration for dwarf_get_TAG_name

int LLVMFuzzerTestOneInput_300(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int tag = *(unsigned int *)data;

    // Initialize a pointer for the TAG name
    const char *tag_name = NULL;

    // Call the function-under-test
    int result = dwarf_get_TAG_name(tag, &tag_name);

    // Optionally, print the result and tag_name for debugging purposes
    // printf("Result: %d, TAG Name: %s\n", result, tag_name ? tag_name : "NULL");

    return 0;
}