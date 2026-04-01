#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_perf_event_opts
    size_t ret_bpf_program__insn_cnt_ujxan = bpf_program__insn_cnt(prog);
    if (ret_bpf_program__insn_cnt_ujxan < 0){
    	return 0;
    }

    struct bpf_link* ret_bpf_program__attach_perf_event_opts_ufvyp = bpf_program__attach_perf_event_opts(prog, (int )ret_bpf_program__insn_cnt_ujxan, NULL);
    if (ret_bpf_program__attach_perf_event_opts_ufvyp == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int result = bpf_program__set_attach_target(prog, 0, target);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to perf_buffer__buffer

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to bpf_program__attach_xdp
    int ret_libbpf_unregister_prog_handler_ujzsy = libbpf_unregister_prog_handler(size);
    if (ret_libbpf_unregister_prog_handler_ujzsy < 0){
    	return 0;
    }

    struct bpf_link* ret_bpf_program__attach_xdp_hvqbk = bpf_program__attach_xdp(prog, ret_libbpf_unregister_prog_handler_ujzsy);
    if (ret_bpf_program__attach_xdp_hvqbk == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    struct bpf_object* ret_bpf_object__open_xowhv = bpf_object__open((const char *)"w");
    if (ret_bpf_object__open_xowhv == NULL){
    	return 0;
    }
    size_t wyxitjxc = -1;

    int ret_perf_buffer__buffer_wjhdx = perf_buffer__buffer(NULL, result, (void **)&ret_bpf_object__open_xowhv, &wyxitjxc);
    if (ret_perf_buffer__buffer_wjhdx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);
    free(target);

    return 0;
}