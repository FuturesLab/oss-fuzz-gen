#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <libdwarf.h> // Assuming the function is part of libdwarf

extern int dwarf_get_FRAME_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_210(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for at least one unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int index = *(const unsigned int *)data;

    // Prepare a non-NULL pointer for the function call
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_FRAME_name(index, &name);

    // Optionally, you can use the result and name for further logic or checks
    // For fuzzing, we generally don't need to do anything with these

    return 0;
}