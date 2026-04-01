#include <stddef.h>
#include <stdint.h>
#include <libdwarf.h>

int LLVMFuzzerTestOneInput_277(const uint8_t *data, size_t size) {
    unsigned int access_code;
    const char *access_name = NULL;

    // Ensure that the size is sufficient to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    access_code = *(const unsigned int *)data;

    // Call the function-under-test
    int result = dwarf_get_ACCESS_name(access_code, &access_name);

    // Optionally, you could add checks or further processing based on `result` and `access_name`

    return 0;
}