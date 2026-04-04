#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__load to bpf_map__update_elem
    int ret_bpf_link__destroy_dxiro = bpf_link__destroy(NULL);
    if (ret_bpf_link__destroy_dxiro < 0){
    	return 0;
    }
    int ret_libbpf_unregister_prog_handler_ghthy = libbpf_unregister_prog_handler(-1);
    if (ret_libbpf_unregister_prog_handler_ghthy < 0){
    	return 0;
    }
    __u64 ret_bpf_map__map_extra_opiwu = bpf_map__map_extra(NULL);
    char hhtbibcv[1024] = "qpidq";

    int ret_bpf_map__update_elem_sxyta = bpf_map__update_elem(NULL, hhtbibcv, (size_t )ret_bpf_link__destroy_dxiro, (const void *)obj, (size_t )ret_libbpf_unregister_prog_handler_ghthy, ret_bpf_map__map_extra_opiwu);
    if (ret_bpf_map__update_elem_sxyta < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_bpf_object__pin_maps_rezow = bpf_object__pin(obj, (const char *)"w");
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_object__pin_maps_rezow < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}