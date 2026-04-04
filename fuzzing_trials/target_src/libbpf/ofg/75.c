#include <stddef.h>
#include <stdint.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to interpret as a bpf_attach_type
    if (size < sizeof(enum bpf_attach_type)) {
        return 0;
    }

    // Cast the input data to bpf_attach_type
    enum bpf_attach_type attach_type = *(enum bpf_attach_type *)data;

    // Call the function-under-test
    const char *result = libbpf_bpf_attach_type_str(attach_type);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result != NULL) {
        (void)result; // No-op to use the result
    }

    return 0;
}