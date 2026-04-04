#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a bpf_link_type value
    if (size < sizeof(enum bpf_link_type)) {
        return 0;
    }

    // Extract a bpf_link_type value from the input data
    enum bpf_link_type link_type = *(enum bpf_link_type *)data;

    // Call the function-under-test
    const char *result = libbpf_bpf_link_type_str(link_type);

    // Use the result in some way to prevent any compiler optimizations from removing the call
    if (result) {
        // For fuzzing, we don't need to do anything with the result
    }

    return 0;
}