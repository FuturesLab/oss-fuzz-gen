#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);
    if (obj == NULL) {
        return 0; // If object creation fails, exit early
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to bpf_object__unpin_maps


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__unpin_maps with bpf_object__pin
    int ret_bpf_object__unpin_maps_lojbw = bpf_object__pin(obj, (const char *)"w");
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_object__unpin_maps_lojbw < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__unpin_maps to bpf_object__pin_maps

    int ret_bpf_object__pin_maps_apraa = bpf_object__pin_maps(obj, (const char *)"w");
    if (ret_bpf_object__pin_maps_apraa < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int result = bpf_object__prepare(obj);

    // Clean up
    bpf_object__close(obj);

    return 0;
}