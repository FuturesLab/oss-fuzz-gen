#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test
        int result = bpf_object__prepare(obj);

        // Clean up the bpf_object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__unpin_programs


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__unpin_programs with bpf_object__pin

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_object__pin
        int ret_bpf_object__unpin_programs_xzkno = bpf_object__pin(obj, (const char *)"w");
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_bpf_object__unpin_programs_xzkno < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to bpf_map__get_next_key
    size_t ret_bpf_program__insn_cnt_daeef = bpf_program__insn_cnt(NULL);
    if (ret_bpf_program__insn_cnt_daeef < 0){
    	return 0;
    }

    int ret_bpf_map__get_next_key_edmks = bpf_map__get_next_key(NULL, NULL, (void *)obj, ret_bpf_program__insn_cnt_daeef);
    if (ret_bpf_map__get_next_key_edmks < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}