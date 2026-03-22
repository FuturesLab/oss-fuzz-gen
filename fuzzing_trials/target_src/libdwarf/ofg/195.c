#include <stddef.h>
#include <stdint.h>
#include <dwarf.h>
#include <libdwarf.h> // Include this header for DW_DLV_OK

extern int dwarf_get_LNE_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int index = *(unsigned int *)data;
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_LNE_name(index, &name);

    // Use the result and name in some way to avoid compiler optimizations
    if (result == DW_DLV_OK && name != NULL) {
        // Print the name or perform other operations
        // This part is just to demonstrate the use of the result
        // In a real fuzzing scenario, we might log or analyze the output
        (void)name; // Avoid unused variable warning
    }

    return 0;
}