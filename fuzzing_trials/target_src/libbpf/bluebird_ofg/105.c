#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
        int result = bpf_object__load(obj);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Clean up the bpf_object

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to bpf_object__next_program

    struct bpf_program* ret_bpf_object__next_program_dknpu = bpf_object__next_program(obj, NULL);
    if (ret_bpf_object__next_program_dknpu == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_raw_tracepoint


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__attach_raw_tracepoint
    const char rnqkfonq[1024] = "cbdkc";

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__insns


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_usdt
    const char xqvyakuh[1024] = "gtvrj";
    const char xtasyeky[1024] = "ygbwc";

    struct bpf_link* ret_bpf_program__attach_usdt_jvpav = bpf_program__attach_usdt(ret_bpf_object__next_program_dknpu, 0, xqvyakuh, xtasyeky, (const char *)"w", NULL);
    if (ret_bpf_program__attach_usdt_jvpav == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    const struct bpf_insn* ret_bpf_program__insns_nrsjo = bpf_program__insns(ret_bpf_object__next_program_dknpu);
    if (ret_bpf_program__insns_nrsjo == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    struct bpf_link* ret_bpf_program__attach_raw_tracepoint_vqfkl = bpf_program__attach_raw_tracepoint(ret_bpf_object__next_program_dknpu, rnqkfonq);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bpf_program__attach_raw_tracepoint_vqfkl == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}