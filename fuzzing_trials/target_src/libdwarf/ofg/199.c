#include <stddef.h>
#include <stdint.h>
#include <dwarf.h>
#include <libdwarf.h>  // Include the header file that defines DW_DLV_OK

extern int dwarf_get_AT_name(unsigned int attr, const char **name);

int LLVMFuzzerTestOneInput_199(const uint8_t *data, size_t size) {
    // Ensure that the size of the data is sufficient to extract an unsigned int.
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data.
    unsigned int attr = *(const unsigned int *)data;

    // Declare a pointer to hold the attribute name.
    const char *name = NULL;

    // Call the function-under-test.
    int result = dwarf_get_AT_name(attr, &name);

    // Use the result and name in some way to avoid compiler optimizations.
    if (result == DW_DLV_OK && name != NULL) {
        // Do something with the name, e.g., print it.
        // Note: In a real fuzzing scenario, printing might not be desired.
        // printf("Attribute name: %s\n", name);
    }

    return 0;
}