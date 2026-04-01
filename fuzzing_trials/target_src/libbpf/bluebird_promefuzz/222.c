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

int LLVMFuzzerTestOneInput_222(const uint8_t *Data, size_t Size) {
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
    size_t insn_cnt = bpf_program__insn_cnt(prog);

    // Fuzz bpf_program__set_insns
    ret = bpf_program__set_insns(prog, insns, insn_cnt);
    
    // Fuzz bpf_program__expected_attach_type
    enum bpf_attach_type attach_type = bpf_program__expected_attach_type(prog);

    // Fuzz bpf_program__attach_cgroup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__expected_attach_type to libbpf_find_vmlinux_btf_id


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of libbpf_find_vmlinux_btf_id
    int ret_libbpf_find_vmlinux_btf_id_kgzrs = libbpf_find_vmlinux_btf_id((const char *)"r", attach_type);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_libbpf_find_vmlinux_btf_id_kgzrs < 0){
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