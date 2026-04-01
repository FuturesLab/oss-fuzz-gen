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

int LLVMFuzzerTestOneInput_202(const uint8_t *Data, size_t Size) {
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

    int ret_bpf_map__set_inner_map_fd_sgasp = bpf_map__set_inner_map_fd(ret_bpf_map__inner_map_tkcat, ret_libbpf_find_vmlinux_btf_id_kgzrs);
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_link__update_program to bpf_program__attach_freplace
        unsigned int ret_bpf_object__kversion_tqopj = bpf_object__kversion(NULL);
        if (ret_bpf_object__kversion_tqopj < 0){
        	return 0;
        }

        struct bpf_link* ret_bpf_program__attach_freplace_ngddx = bpf_program__attach_freplace(prog, (int )ret_bpf_object__kversion_tqopj, NULL);
        if (ret_bpf_program__attach_freplace_ngddx == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__attach_freplace to bpf_object__open_mem
        struct bpf_object_skeleton nciyodcn;
        memset(&nciyodcn, 0, sizeof(nciyodcn));
        int ret_bpf_object__attach_skeleton_mpklm = bpf_object__attach_skeleton(&nciyodcn);
        if (ret_bpf_object__attach_skeleton_mpklm < 0){
        	return 0;
        }

        struct bpf_object* ret_bpf_object__open_mem_wutwp = bpf_object__open_mem((const void *)ret_bpf_program__attach_freplace_ngddx, (size_t )ret_bpf_object__attach_skeleton_mpklm, NULL);
        if (ret_bpf_object__open_mem_wutwp == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}