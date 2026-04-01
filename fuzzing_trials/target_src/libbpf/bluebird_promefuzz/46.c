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

int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__load with bpf_object__prepare
    if (bpf_object__prepare(obj) < 0)
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_uprobe_multi
    const char feeqhwmw[1024] = "vuuuu";


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of bpf_program__attach_uprobe_multi
    struct bpf_link* ret_bpf_program__attach_uprobe_multi_twcjw = bpf_program__attach_uprobe_multi(prog, 0, (const char *)"w", (const char *)"r", NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bpf_program__attach_uprobe_multi_twcjw == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    size_t insn_cnt = bpf_program__insn_cnt(prog);

    // Fuzz bpf_program__set_insns
    ret = bpf_program__set_insns(prog, insns, insn_cnt);
    
    // Fuzz bpf_program__expected_attach_type

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_insns to bpf_program__log_buf
    int ret_bpf_object__load_dejci = bpf_object__load(obj);
    if (ret_bpf_object__load_dejci < 0){
    	return 0;
    }

    const char* ret_bpf_program__log_buf_ftmwb = bpf_program__log_buf(prog, (size_t *)&ret_bpf_object__load_dejci);
    if (ret_bpf_program__log_buf_ftmwb == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    enum bpf_attach_type attach_type = bpf_program__expected_attach_type(prog);

    // Fuzz bpf_program__attach_cgroup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__expected_attach_type to libbpf_find_vmlinux_btf_id

    int ret_libbpf_find_vmlinux_btf_id_kgzrs = libbpf_find_vmlinux_btf_id(NULL, attach_type);
    if (ret_libbpf_find_vmlinux_btf_id_kgzrs < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from libbpf_find_vmlinux_btf_id to bpf_map__set_inner_map_fd
    struct bpf_map* ret_bpf_map__inner_map_tkcat = bpf_map__inner_map(NULL);
    if (ret_bpf_map__inner_map_tkcat == NULL){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_map__set_inner_map_fd
    int ret_bpf_map__set_inner_map_fd_sgasp = bpf_map__set_inner_map_fd(ret_bpf_map__inner_map_tkcat, 64);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bpf_map__set_inner_map_fd_sgasp < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    link = bpf_program__attach_cgroup(prog, cgroup_fd);
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
        bpf_object__close(obj);
    }

    return 0;
}