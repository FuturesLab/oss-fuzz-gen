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

int LLVMFuzzerTestOneInput_215(const uint8_t *Data, size_t Size) {
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
    ret = bpf_program__set_insns(prog, insns, insn_cnt);
    
    // Fuzz bpf_program__expected_attach_type

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_insns to bpf_program__attach_kprobe_opts

    struct bpf_link* ret_bpf_program__attach_kprobe_opts_fyvdx = bpf_program__attach_kprobe_opts(prog, NULL, NULL);
    if (ret_bpf_program__attach_kprobe_opts_fyvdx == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    enum bpf_attach_type attach_type = bpf_program__expected_attach_type(prog);

    // Fuzz bpf_program__attach_cgroup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__expected_attach_type to libbpf_find_vmlinux_btf_id


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__expected_attach_type to libbpf_attach_type_by_name

    int ret_libbpf_attach_type_by_name_bmoqm = libbpf_attach_type_by_name((const char *)Data, &attach_type);
    if (ret_libbpf_attach_type_by_name_bmoqm < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_libbpf_find_vmlinux_btf_id_kgzrs = libbpf_find_vmlinux_btf_id(NULL, attach_type);
    if (ret_libbpf_find_vmlinux_btf_id_kgzrs < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_program__attach_cgroup with bpf_program__attach_xdp
    link = bpf_program__attach_xdp(prog, cgroup_fd);
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
        bpf_object__close(obj);
    }

    return 0;
}