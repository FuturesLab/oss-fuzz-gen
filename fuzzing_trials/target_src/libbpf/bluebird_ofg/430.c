#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_430(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);
    if (obj == NULL) {
        return 0; // If object creation fails, exit early
    }

    // Call the function-under-test
    int result = bpf_object__prepare(obj);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prepare to bpf_object__pin_maps

    int ret_bpf_object__pin_maps_vhybf = bpf_object__pin_maps(obj, NULL);
    if (ret_bpf_object__pin_maps_vhybf < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}