#include <stddef.h>
#include <stdint.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int num_cpus = libbpf_num_possible_cpus();

    // Use the result in some way to avoid compiler optimizations removing the call
    if (num_cpus > 0) {
        // Do something trivial with num_cpus
        volatile int dummy = num_cpus;
        (void)dummy;
    }

    return 0;
}