#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_431(const uint8_t *data, size_t size) {

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bpf_object__open_mem
    struct bpf_object *obj = bpf_object__open_mem((const void *)data, size, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (obj == NULL) {
        return 0; // If object creation fails, exit early
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to bpf_object__unpin_maps

    int ret_bpf_object__unpin_maps_lojbw = bpf_object__unpin_maps(obj, (const char *)"w");
    if (ret_bpf_object__unpin_maps_lojbw < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int result = bpf_object__prepare(obj);

    // Clean up
    bpf_object__close(obj);

    return 0;
}