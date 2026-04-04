#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    struct bpf_program *prog;
    int attach_type;
    char *target;
    struct bpf_object *obj;

    // Ensure data size is sufficient for creating a string
    if (size < 1) {
        return 0;
    }

    // Load a dummy BPF object to initialize a bpf_program
    obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0;
    }

    // Get the first program from the BPF object
    prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        return 0;
    }

    // Use the first byte of data to determine the attach_type
    attach_type = (int)data[0];

    // Allocate memory for the target string and copy data into it

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_xdp

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__set_ifindex

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_uprobe_opts

    struct bpf_link* ret_bpf_program__attach_uprobe_opts_adeiv = bpf_program__attach_uprobe_opts(prog, 0, (const char *)"w", 1, NULL);
    if (ret_bpf_program__attach_uprobe_opts_adeiv == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    __u32 ret_bpf_map__btf_value_type_id_vsubl = bpf_map__btf_value_type_id(NULL);

    bpf_program__set_ifindex(prog, ret_bpf_map__btf_value_type_id_vsubl);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__load with bpf_object__prepare
    int ret_bpf_object__load_jqurq = bpf_object__prepare(obj);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_object__load_jqurq < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_program__attach_xdp with bpf_program__attach_perf_event

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__attach_perf_event

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__load to bpf_program__set_log_buf
    bpf_program__unload(prog);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__unload to bpf_program__attach_netns

    struct bpf_link* ret_bpf_program__attach_netns_sumay = bpf_program__attach_netns(prog, 0);
    if (ret_bpf_program__attach_netns_sumay == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_bpf_program__set_log_buf_mrtbk = bpf_program__set_log_buf(prog, NULL, (size_t )ret_bpf_object__load_jqurq);
    if (ret_bpf_program__set_log_buf_mrtbk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    struct bpf_link* ret_bpf_program__attach_xdp_vvvez = bpf_program__attach_perf_event(prog, 0);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_program__attach_xdp_vvvez == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    target = (char *)malloc(size);
    if (target == NULL) {
        bpf_object__close(obj);
        return 0;
    }
    memcpy(target, data + 1, size - 1);
    target[size - 1] = '\0'; // Ensure null-termination

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__set_attach_target
    bpf_program__set_attach_target(prog, 0, target);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    free(target);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__kversion

        unsigned int ret_bpf_object__kversion_gmwuy = bpf_object__kversion(obj);
        if (ret_bpf_object__kversion_gmwuy < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__token_fd

        int ret_bpf_object__token_fd_zxxqt = bpf_object__token_fd(obj);
        if (ret_bpf_object__token_fd_zxxqt < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to perf_buffer__buffer

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__token_fd to libbpf_strerror
        int ret_bpf_object__open_subskeleton_bvkpr = bpf_object__open_subskeleton(NULL);
        if (ret_bpf_object__open_subskeleton_bvkpr < 0){
        	return 0;
        }

        int ret_libbpf_strerror_mogmn = libbpf_strerror(ret_bpf_object__open_subskeleton_bvkpr, (char *)"r", (size_t )ret_bpf_object__token_fd_zxxqt);
        if (ret_libbpf_strerror_mogmn < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        size_t ret_bpf_program__insn_cnt_ckkfi = bpf_program__insn_cnt(prog);
        if (ret_bpf_program__insn_cnt_ckkfi < 0){
        	return 0;
        }
        int ret_libbpf_unregister_prog_handler_fhumd = libbpf_unregister_prog_handler(1);
        if (ret_libbpf_unregister_prog_handler_fhumd < 0){
        	return 0;
        }

        int ret_perf_buffer__buffer_rayhs = perf_buffer__buffer(NULL, (int )ret_bpf_program__insn_cnt_ckkfi, (void **)&obj, (size_t *)&ret_libbpf_unregister_prog_handler_fhumd);
        if (ret_perf_buffer__buffer_rayhs < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}