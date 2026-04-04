#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);
    if (obj == NULL) {
        return 0; // If object creation fails, exit early
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
    int result = bpf_object__load(obj);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prepare to bpf_object__pin_maps


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__pin_maps with bpf_object__pin
    int ret_bpf_object__pin_maps_rezow = bpf_object__pin(obj, (const char *)"w");
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_object__pin_maps_rezow < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}