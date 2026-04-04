#include <stddef.h>
#include <stdint.h>
#include <linux/bpf.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an integer value
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer value from the input data
    int prog_type = *(const int *)data;

    // Call the function-under-test
    const char *result = libbpf_bpf_prog_type_str((enum bpf_prog_type)prog_type);

    // Use the result to avoid any compiler optimizations that might remove the call
    if (result != NULL) {
        // Do something trivial with the result
        volatile const char *dummy = result;
        (void)dummy;
    }

    return 0;
}