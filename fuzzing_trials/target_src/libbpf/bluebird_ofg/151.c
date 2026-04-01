#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
        int result = bpf_object__load(obj);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Clean up the bpf_object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__unpin_programs


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__unpin_programs with bpf_object__pin

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_object__pin
        int ret_bpf_object__unpin_programs_xzkno = bpf_object__pin(obj, NULL);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_bpf_object__unpin_programs_xzkno < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__set_kversion

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_map__btf_value_type_id with bpf_map__btf_key_type_id
        __u32 ret_bpf_map__btf_value_type_id_hpwzo = bpf_map__btf_key_type_id(NULL);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        int ret_bpf_object__set_kversion_dzcld = bpf_object__set_kversion(obj, ret_bpf_map__btf_value_type_id_hpwzo);
        if (ret_bpf_object__set_kversion_dzcld < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}