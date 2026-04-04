#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_413(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);
    if (obj == NULL) {
        return 0; // If object creation fails, exit early
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to bpf_object__unpin_maps
    const char yyjbpowx[1024] = "nfmlf";


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__unpin_maps with bpf_object__pin_programs
    int ret_bpf_object__unpin_maps_ijmuh = bpf_object__pin_programs(obj, yyjbpowx);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_object__unpin_maps_ijmuh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__unpin_maps to libbpf_probe_bpf_prog_type

    int ret_libbpf_probe_bpf_prog_type_ymotg = libbpf_probe_bpf_prog_type(0, (const void *)obj);
    if (ret_libbpf_probe_bpf_prog_type_ymotg < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int result = bpf_object__prepare(obj);

    // Clean up
    bpf_object__close(obj);

    return 0;
}