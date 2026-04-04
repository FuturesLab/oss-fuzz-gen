#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_432(const uint8_t *data, size_t size) {

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bpf_object__open_mem
    struct bpf_object *obj = bpf_object__open_mem((const void *)data, size, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (obj == NULL) {
        return 0; // If object creation fails, exit early
    }

    // Call the function-under-test
    int result = bpf_object__prepare(obj);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prepare to bpf_object__pin_maps

    int ret_bpf_object__pin_maps_rezow = bpf_object__pin_maps(obj, (const char *)"w");
    if (ret_bpf_object__pin_maps_rezow < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_map__lookup_elem
    struct bpf_object* ret_bpf_object__open_uzkst = bpf_object__open(NULL);
    if (ret_bpf_object__open_uzkst == NULL){
    	return 0;
    }

    int ret_bpf_map__lookup_elem_uvwus = bpf_map__lookup_elem(NULL, (const void *)ret_bpf_object__open_uzkst, -1, (void *)obj, (size_t )result, 0);
    if (ret_bpf_map__lookup_elem_uvwus < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}