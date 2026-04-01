#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>

extern int dwarf_get_OP_name(unsigned int op, const char **op_name);

int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int op = *(unsigned int *)data;
    const char *op_name = NULL;

    // Call the function-under-test
    int result = dwarf_get_OP_name(op, &op_name);

    // Optionally, you can perform checks or use the result and op_name
    // For fuzzing purposes, the primary goal is to call the function
    // and observe its behavior with various inputs.

    return 0;
}