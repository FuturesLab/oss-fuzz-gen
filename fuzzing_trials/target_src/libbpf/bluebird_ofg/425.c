#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_425(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prepare to bpf_object__set_kversion

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prepare to bpf_program__attach_uprobe_opts

    struct bpf_link* ret_bpf_program__attach_uprobe_opts_qjirx = bpf_program__attach_uprobe_opts(NULL, 0, NULL, (size_t )result, NULL);
    if (ret_bpf_program__attach_uprobe_opts_qjirx == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    __u32 ret_bpf_map__btf_value_type_id_oodsp = bpf_map__btf_value_type_id(NULL);

    int ret_bpf_object__set_kversion_syesv = bpf_object__set_kversion(obj, ret_bpf_map__btf_value_type_id_oodsp);
    if (ret_bpf_object__set_kversion_syesv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}