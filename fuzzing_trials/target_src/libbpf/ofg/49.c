#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    struct bpf_object *obj;
    char *pin_path;
    int result;

    // Initialize a bpf_object
    obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0;
    }

    // Allocate memory for pin_path and ensure it's null-terminated
    pin_path = (char *)malloc(size + 1);
    if (!pin_path) {
        bpf_object__close(obj);
        return 0;
    }
    memcpy(pin_path, data, size);
    pin_path[size] = '\0';  // Ensure null-termination

    // Call the function-under-test
    result = bpf_object__pin_maps(obj, pin_path);

    // Clean up
    free(pin_path);
    bpf_object__close(obj);

    return 0;
}