#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_422(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to bpf_object__prepare

    int ret_bpf_object__prepare_zhlgw = bpf_object__prepare(obj);
    if (ret_bpf_object__prepare_zhlgw < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__next_program with bpf_object__prev_program
    prog = bpf_object__prev_program(obj, NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (!prog) {
        bpf_object__close(obj);
        return 0;
    }

    // Use the first byte of data to determine the attach_type
    attach_type = (int)data[0];

    // Allocate memory for the target string and copy data into it

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__line_info

    struct bpf_line_info* ret_bpf_program__line_info_iblci = bpf_program__line_info(prog);
    if (ret_bpf_program__line_info_iblci == NULL){
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of bpf_program__set_attach_target
    bpf_program__set_attach_target(prog, 64, (const char *)"w");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to bpf_program__attach_uprobe

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_program__autoattach with bpf_program__autoload
    bool ret_bpf_program__autoattach_cmwkc = bpf_program__autoload(prog);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_program__autoattach_cmwkc == 0){
    	return 0;
    }
    int ret_bpf_object__load_nowqw = bpf_object__load(obj);
    if (ret_bpf_object__load_nowqw < 0){
    	return 0;
    }

    struct bpf_link* ret_bpf_program__attach_uprobe_banit = bpf_program__attach_uprobe(prog, ret_bpf_program__autoattach_cmwkc, 0, (const char *)"r", (size_t )ret_bpf_object__load_nowqw);
    if (ret_bpf_program__attach_uprobe_banit == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__attach_uprobe to bpf_map__update_elem
    const char njhmsbjr[1024] = "ykkij";
    struct bpf_object* ret_bpf_object__open_jgfql = bpf_object__open(njhmsbjr);
    if (ret_bpf_object__open_jgfql == NULL){
    	return 0;
    }
    size_t ret_bpf_program__insn_cnt_wiswd = bpf_program__insn_cnt(prog);
    if (ret_bpf_program__insn_cnt_wiswd < 0){
    	return 0;
    }

    int ret_bpf_map__update_elem_rszur = bpf_map__update_elem(NULL, (const void *)ret_bpf_object__open_jgfql, ret_bpf_program__insn_cnt_wiswd, (const void *)ret_bpf_program__attach_uprobe_banit, (size_t )ret_bpf_object__prepare_zhlgw, 0);
    if (ret_bpf_map__update_elem_rszur < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(target);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__kversion

        unsigned int ret_bpf_object__kversion_gmwuy = bpf_object__kversion(obj);
        if (ret_bpf_object__kversion_gmwuy < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__set_kversion

        int ret_bpf_object__set_kversion_dzwee = bpf_object__set_kversion(obj, 0);
        if (ret_bpf_object__set_kversion_dzwee < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__set_kversion to bpf_program__attach_perf_event


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_program__attach_perf_event with bpf_program__attach_cgroup
        struct bpf_link* ret_bpf_program__attach_perf_event_pygqr = bpf_program__attach_cgroup(prog, ret_bpf_object__set_kversion_dzwee);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_bpf_program__attach_perf_event_pygqr == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__name

        const char* ret_bpf_object__name_bscvn = bpf_object__name(obj);
        if (ret_bpf_object__name_bscvn == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}