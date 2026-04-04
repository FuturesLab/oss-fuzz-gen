#include <stddef.h>
#include <stdint.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    struct bpf_object *obj = NULL;

    // Initialize a bpf_object using the data
    obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0;
    }

    // Call the function-under-test
    const char *name = bpf_object__name(obj);

    // Clean up
    if (obj) {
        bpf_object__close(obj);
    }

    return 0;
}