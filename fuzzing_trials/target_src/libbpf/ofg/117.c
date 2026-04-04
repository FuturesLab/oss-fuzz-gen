#include <stddef.h>
#include <stdint.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    struct bpf_object *obj;
    const char *name;

    // Initialize a bpf_object with some valid data
    // For fuzzing purposes, we will simulate a valid bpf_object
    // In a real-world scenario, this would be properly initialized
    obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test
        name = bpf_object__name(obj);

        // Use the name in some way to avoid compiler optimizations removing the call
        if (name != NULL) {
            // Just a dummy operation to use the name
            volatile size_t name_length = 0;
            while (name[name_length] != '\0') {
                name_length++;
            }
        }

        // Clean up
        bpf_object__close(obj);
    }

    return 0;
}