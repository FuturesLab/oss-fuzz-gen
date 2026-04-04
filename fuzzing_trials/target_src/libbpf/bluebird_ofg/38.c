#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);
    if (obj == NULL) {
        return 0; // If object creation fails, exit early
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to bpf_object__unpin_maps
    const char yyjbpowx[1024] = "nfmlf";


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__unpin_maps with bpf_object__unpin_programs

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__unpin_programs with bpf_object__unpin
    int ret_bpf_object__unpin_maps_ijmuh = bpf_object__unpin(obj, yyjbpowx);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_object__unpin_maps_ijmuh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__unpin_maps to libbpf_probe_bpf_prog_type


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of libbpf_probe_bpf_prog_type
    int ret_libbpf_probe_bpf_prog_type_ymotg = libbpf_probe_bpf_prog_type(0, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_libbpf_probe_bpf_prog_type_ymotg < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int result = bpf_object__prepare(obj);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prepare to bpf_map__update_elem
    struct bpf_object_subskeleton wlvpcuyr;
    memset(&wlvpcuyr, 0, sizeof(wlvpcuyr));
    int ret_bpf_object__open_subskeleton_oaunn = bpf_object__open_subskeleton(&wlvpcuyr);
    if (ret_bpf_object__open_subskeleton_oaunn < 0){
    	return 0;
    }
    __u64 ret_bpf_map__map_extra_dbgly = bpf_map__map_extra(NULL);


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of bpf_map__update_elem
    int ret_bpf_map__update_elem_btxtx = bpf_map__update_elem(NULL, (const void *)&wlvpcuyr, (size_t)result, (const void *)obj, 0, ret_bpf_map__map_extra_dbgly);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bpf_map__update_elem_btxtx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}