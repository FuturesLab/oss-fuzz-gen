#include <stdint.h>
#include <stddef.h>

// Assume the function is declared in some header file
int dwarf_get_ISA_name(unsigned int isa, const char **name);

int LLVMFuzzerTestOneInput_216(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int isa = *(unsigned int *)data;
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_ISA_name(isa, &name);

    // Optionally, you can perform further checks or use the 'name' variable
    // For example, ensure 'name' is not NULL if the result indicates success
    if (result == 0 && name != NULL) {
        // Do something with 'name', like logging or further processing
    }

    return 0;
}