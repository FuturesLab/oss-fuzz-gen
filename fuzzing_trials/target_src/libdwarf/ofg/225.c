#include <stdint.h>
#include <stddef.h>

// Assume the function is defined in some external library
extern int dwarf_get_ID_name(unsigned int id, const char **name);

int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int id = *(unsigned int *)data;

    // Prepare a non-NULL pointer for the name
    const char *name = "default_name";

    // Call the function-under-test
    int result = dwarf_get_ID_name(id, &name);

    // Optionally, you can add checks or further processing on the result
    // For example, you might want to log the result or check for specific return values

    return 0;
}