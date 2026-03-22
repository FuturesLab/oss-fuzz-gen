#include <stddef.h>
#include <stdint.h>
#include <dwarf.h>

#ifdef __cplusplus
extern "C" {
#endif

// Function prototype for the function-under-test
int dwarf_get_FORM_name(unsigned int form, const char **name);

int LLVMFuzzerTestOneInput_246(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int form = *((unsigned int *)data);

    // Initialize a pointer for the name
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_FORM_name(form, &name);

    // Optionally, you can add checks or additional logic here
    // For example, you could print the result or the name if needed

    return 0;
}

#ifdef __cplusplus
}
#endif