#include <stddef.h>
#include <stdint.h>
#include <dwarf.h>

extern int dwarf_get_MACINFO_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int macinfo_type;
    const char *name = "";

    // Copy the first four bytes of data to macinfo_type
    macinfo_type = *(const unsigned int *)data;

    // Call the function-under-test
    int result = dwarf_get_MACINFO_name(macinfo_type, &name);

    // Optionally, you can also check the result or use the 'name' variable
    // if needed for further testing or validation

    return 0;
}