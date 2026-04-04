#include <stddef.h>
#include <stdint.h>
#include <stdio.h> // Include for printf to use in the function
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an integer value
    if (size < sizeof(int)) {
        return 0;
    }

    // Cast the first bytes of data to an integer to use as the enum value
    enum bpf_map_type map_type = 
        (enum bpf_map_type)(*(const int*)data);

    // Call the function-under-test
    const char *result = libbpf_bpf_map_type_str(map_type);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // Print the result or perform some operation
        printf("Map type: %s\n", result);
    }

    return 0;
}