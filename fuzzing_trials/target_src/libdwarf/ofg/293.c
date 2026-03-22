#include <stddef.h>
#include <stdint.h>
#include <dwarf.h>

extern int dwarf_get_VIRTUALITY_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_293(const uint8_t *data, size_t size) {
    unsigned int virtuality;
    const char *name = NULL;

    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    virtuality = *(unsigned int *)data;

    // Call the function-under-test
    dwarf_get_VIRTUALITY_name(virtuality, &name);

    return 0;
}