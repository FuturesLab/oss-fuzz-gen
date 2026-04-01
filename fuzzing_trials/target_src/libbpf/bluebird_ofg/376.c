#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_376(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Ensure the data is null-terminated to safely use it as a string
    char *target = (char *)malloc(size + 1);
    if (!target) {
        return 0;
    }
    memcpy(target, data, size);
    target[size] = '\0';

    // Initialize libbpf
    libbpf_set_strict_mode(LIBBPF_STRICT_ALL);

    // Create a new BPF program object
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        free(target);
        return 0;
    }

    struct bpf_program *prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        free(target);
        return 0;
    }

    int attach_type = (int)data[0]; // Use the first byte of data as an integer

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__set_attach_target

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__set_attach_target
    int result = bpf_program__set_attach_target(prog, 64, target);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to perf_buffer__buffer

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bpf_object__open

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to bpf_object__next_program

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to bpf_program__set_autoattach

    bpf_program__set_autoattach(prog, 0);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
    int ret_bpf_object__prepare_juach = bpf_object__load(obj);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_object__prepare_juach < 0){
    	return 0;
    }

    struct bpf_program* ret_bpf_object__next_program_pgwwg = bpf_object__next_program(obj, prog);
    if (ret_bpf_object__next_program_pgwwg == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    struct bpf_object* ret_bpf_object__open_xowhv = bpf_object__open((const char *)"r");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bpf_object__open_xowhv == NULL){
    	return 0;
    }
    size_t wyxitjxc = -1;

    int ret_perf_buffer__buffer_wjhdx = perf_buffer__buffer(NULL, result, (void **)&ret_bpf_object__open_xowhv, &wyxitjxc);
    if (ret_perf_buffer__buffer_wjhdx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from perf_buffer__buffer to bpf_program__pin

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from perf_buffer__buffer to bpf_program__set_insns
    bpf_program__unload(ret_bpf_object__next_program_pgwwg);

    int ret_bpf_program__set_insns_xcmiz = bpf_program__set_insns(ret_bpf_object__next_program_pgwwg, NULL, wyxitjxc);
    if (ret_bpf_program__set_insns_xcmiz < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_program__unload(ret_bpf_object__next_program_pgwwg);

    int ret_bpf_program__pin_hzkig = bpf_program__pin(ret_bpf_object__next_program_pgwwg, &ret_bpf_object__open_xowhv);
    if (ret_bpf_program__pin_hzkig < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);
    free(target);

    return 0;
}