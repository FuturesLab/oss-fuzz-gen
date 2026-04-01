#include <stddef.h>
#include <stdint.h>
#include <libdwarf.h>

int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    unsigned int op = 0;
    const char *op_name = NULL;

    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    op = *((unsigned int *)data);

    // Call the function-under-test
    int result = dwarf_get_OP_name(op, &op_name);

    // Use op_name in some way to avoid compiler optimizations removing it
    if (op_name != NULL) {
        // Print op_name or perform some operation
        // For fuzzing, we generally do not need to do anything with it
    }

    return 0;
}