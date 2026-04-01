#include <stddef.h>
#include <stdint.h>
#include <libdwarf.h>

int LLVMFuzzerTestOneInput_198(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int attr = *(unsigned int *)data;

    // Prepare a pointer for the attribute name
    const char *attr_name = NULL;

    // Call the function-under-test
    int result = dwarf_get_AT_name(attr, &attr_name);

    // Optionally, you can perform checks or print the result for debugging
    // if (result == DW_DLV_OK && attr_name != NULL) {
    //     printf("Attribute Name: %s\n", attr_name);
    // }

    return 0;
}