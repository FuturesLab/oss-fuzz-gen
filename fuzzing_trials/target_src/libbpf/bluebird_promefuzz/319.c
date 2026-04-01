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

int LLVMFuzzerTestOneInput_319(const uint8_t *Data, size_t Size) {
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
    prog = bpf_object__next_program(obj, NULL);
    if (!prog)
        {
        goto cleanup;
    }

    // Fuzz bpf_program__insn_cnt

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_link__update_program
    struct bpf_link* ret_bpf_program__attach_tyync = bpf_program__attach(prog);
    if (ret_bpf_program__attach_tyync == NULL){
    	return 0;
    }

    int ret_bpf_link__update_program_slnti = bpf_link__update_program(ret_bpf_program__attach_tyync, prog);
    if (ret_bpf_link__update_program_slnti < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    size_t insn_cnt = bpf_program__insn_cnt(prog);

    // Fuzz bpf_program__set_insns

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__insn_cnt to libbpf_strerror

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of libbpf_unregister_prog_handler
    int ret_libbpf_unregister_prog_handler_drxmw = libbpf_unregister_prog_handler(-1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_libbpf_unregister_prog_handler_drxmw < 0){
    	return 0;
    }

    int ret_libbpf_strerror_pbvdv = libbpf_strerror((int )insn_cnt, (char *)"w", (size_t )ret_libbpf_unregister_prog_handler_drxmw);
    if (ret_libbpf_strerror_pbvdv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    ret = bpf_program__set_insns(prog, insns, insn_cnt);
    
    // Fuzz bpf_program__expected_attach_type
    enum bpf_attach_type attach_type = bpf_program__expected_attach_type(prog);

    // Fuzz bpf_program__attach_cgroup

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_program__attach_cgroup with bpf_program__attach_perf_event

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__attach_perf_event

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_program__attach_perf_event with bpf_program__attach_sockmap

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_program__attach_sockmap with bpf_program__attach_xdp
    link = bpf_program__attach_xdp(prog, 1);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_link__destroy with bpf_link__unpin
        bpf_link__unpin(link);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }
    if (obj)
        {
        bpf_object__close(obj);
    }

    return 0;
}