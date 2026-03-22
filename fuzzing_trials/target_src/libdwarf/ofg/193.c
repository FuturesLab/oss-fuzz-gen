#include <stddef.h>
#include <stdint.h>

// Assume the function is declared in some header file.
int dwarf_get_UT_name(unsigned int ut, const char **ut_name);

int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for extracting an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int ut = *(unsigned int *)data;

    // Define a pointer for the name
    const char *ut_name = NULL;

    // Call the function-under-test
    int result = dwarf_get_UT_name(ut, &ut_name);

    // Use the result or ut_name if needed for further testing
    // For now, we just return 0 to indicate the fuzzer can continue
    return 0;
}