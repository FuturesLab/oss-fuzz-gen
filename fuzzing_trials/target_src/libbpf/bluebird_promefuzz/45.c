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

int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
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
    ret = bpf_program__set_insns(prog, insns, -1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    
    // Fuzz bpf_program__expected_attach_type

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_insns to bpf_program__attach_kprobe_opts


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_insns to bpf_program__attach_uprobe


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_insns to bpf_program__attach_tcx

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_insns to bpf_program__attach_uprobe
    bool ret_bpf_program__autoload_bdawu = bpf_program__autoload(prog);
    if (ret_bpf_program__autoload_bdawu == 0){
    	return 0;
    }

    struct bpf_link* ret_bpf_program__attach_uprobe_nwajr = bpf_program__attach_uprobe(prog, ret_bpf_program__autoload_bdawu, 0, (const char *)"w", -1);
    if (ret_bpf_program__attach_uprobe_nwajr == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    unsigned int ret_bpf_object__kversion_jgwka = bpf_object__kversion(NULL);
    if (ret_bpf_object__kversion_jgwka < 0){
    	return 0;
    }

    struct bpf_link* ret_bpf_program__attach_tcx_codjd = bpf_program__attach_tcx(prog, (int )ret_bpf_object__kversion_jgwka, NULL);
    if (ret_bpf_program__attach_tcx_codjd == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    struct bpf_link* ret_bpf_program__attach_uprobe_lknrc = bpf_program__attach_uprobe(prog, 1, 0, (const char *)Data, 64);
    if (ret_bpf_program__attach_uprobe_lknrc == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    struct bpf_link* ret_bpf_program__attach_kprobe_opts_fyvdx = bpf_program__attach_kprobe_opts(prog, NULL, NULL);
    if (ret_bpf_program__attach_kprobe_opts_fyvdx == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    enum bpf_attach_type attach_type = bpf_program__expected_attach_type(prog);

    // Fuzz bpf_program__attach_cgroup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__expected_attach_type to libbpf_find_vmlinux_btf_id


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__expected_attach_type to libbpf_attach_type_by_name

    int ret_libbpf_attach_type_by_name_gmlan = libbpf_attach_type_by_name(NULL, &attach_type);
    if (ret_libbpf_attach_type_by_name_gmlan < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of libbpf_find_vmlinux_btf_id
    const char geczoqfo[1024] = "awmdx";
    int ret_libbpf_find_vmlinux_btf_id_kgzrs = libbpf_find_vmlinux_btf_id(geczoqfo, attach_type);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_link__destroy with bpf_link__detach
        bpf_link__detach(link);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }
    if (obj)
        {

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_link__update_program to bpf_program__attach_cgroup_opts
        int ret_bpf_link__unpin_eqphh = bpf_link__unpin(ret_bpf_program__attach_kprobe_opts_fyvdx);
        if (ret_bpf_link__unpin_eqphh < 0){
        	return 0;
        }

        struct bpf_link* ret_bpf_program__attach_cgroup_opts_tnkeq = bpf_program__attach_cgroup_opts(prog, ret_bpf_link__unpin_eqphh, NULL);
        if (ret_bpf_program__attach_cgroup_opts_tnkeq == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}