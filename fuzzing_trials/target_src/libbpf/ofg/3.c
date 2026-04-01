#include <stddef.h>
#include <stdint.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    enum bpf_prog_type prog_type = BPF_PROG_TYPE_UNSPEC;
    const void *opts = (const void *)data;

    // Ensure size is sufficient for the options structure
    if (size < sizeof(void *)) {
        return 0;
    }

    // Call the function-under-test
    int result = libbpf_probe_bpf_prog_type(prog_type, opts);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}