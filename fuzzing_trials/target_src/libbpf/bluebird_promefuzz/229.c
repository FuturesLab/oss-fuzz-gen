#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "/src/libbpf/include/uapi/linux/fcntl.h"
#include <unistd.h>
#include "libbpf.h"

static void initialize_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_229(const uint8_t *Data, size_t Size) {
    struct bpf_object *obj = NULL;
    struct bpf_program *prog = NULL;
    struct bpf_link *link = NULL;
    struct bpf_insn insns[10];
    int cgroup_fd = -1;
    int ret;

    // Initialize dummy file with fuzzer data
    initialize_dummy_file(Data, Size);

    // Attempt to open a BPF object from the dummy file
    obj = bpf_object__open_file("./dummy_file", NULL);
    if (!obj)
        {
        return 0;
    }

    // Load the BPF object
    if (bpf_object__load(obj) < 0)
        {
        goto cleanup;
    }

    // Get the first program

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__next_program with bpf_object__prev_program
    prog = bpf_object__prev_program(obj, NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (!prog)
        {
        goto cleanup;
    }

    // Fuzz bpf_program__insn_cnt
    size_t insn_cnt = bpf_program__insn_cnt(prog);

    // Fuzz bpf_program__set_insns

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of bpf_program__set_insns

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of bpf_program__set_insns
    ret = bpf_program__set_insns(prog, insns, 64);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    
    // Fuzz bpf_program__expected_attach_type
    enum bpf_attach_type attach_type = bpf_program__expected_attach_type(prog);

    // Fuzz bpf_program__attach_cgroup

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_program__attach_cgroup with bpf_program__attach_perf_event

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__attach_perf_event

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__attach_perf_event

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__expected_attach_type to libbpf_register_prog_handler

    int ret_libbpf_register_prog_handler_mqhpz = libbpf_register_prog_handler((const char *)"w", 0, attach_type, NULL);
    if (ret_libbpf_register_prog_handler_mqhpz < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    link = bpf_program__attach_perf_event(prog, 64);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (link) {
        // Fuzz bpf_link__update_program
        ret = bpf_link__update_program(link, prog);
    }

cleanup:
    // Clean up
    if (link)
        {
        bpf_link__destroy(link);
    }
    if (obj)
        {

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__attach_perf_event to bpf_link__destroy

    int ret_bpf_link__destroy_ekjyz = bpf_link__destroy(link);
    if (ret_bpf_link__destroy_ekjyz < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__next_program

        struct bpf_program* ret_bpf_object__next_program_elgqx = bpf_object__next_program(obj, NULL);
        if (ret_bpf_object__next_program_elgqx == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}