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

int LLVMFuzzerTestOneInput_165(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
    if (bpf_object__load(obj) < 0)
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_kprobe_multi_opts

    struct bpf_link* ret_bpf_program__attach_kprobe_multi_opts_dctnz = bpf_program__attach_kprobe_multi_opts(prog, (const char *)"r", NULL);
    if (ret_bpf_program__attach_kprobe_multi_opts_dctnz == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    size_t insn_cnt = bpf_program__insn_cnt(prog);

    // Fuzz bpf_program__set_insns

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__insn_cnt to bpf_program__set_attach_target
    bpf_program__unload(prog);

    int ret_bpf_program__set_attach_target_evqoe = bpf_program__set_attach_target(prog, (int )insn_cnt, (const char *)"w");
    if (ret_bpf_program__set_attach_target_evqoe < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    ret = bpf_program__set_insns(prog, insns, insn_cnt);
    
    // Fuzz bpf_program__expected_attach_type

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_insns to libbpf_unregister_prog_handler


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_insns to bpf_program__pin

    int ret_bpf_program__pin_egjkl = bpf_program__pin(prog, (const char *)"w");
    if (ret_bpf_program__pin_egjkl < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_libbpf_unregister_prog_handler_nmikc = libbpf_unregister_prog_handler(ret);
    if (ret_libbpf_unregister_prog_handler_nmikc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    enum bpf_attach_type attach_type = bpf_program__expected_attach_type(prog);

    // Fuzz bpf_program__attach_cgroup
    link = bpf_program__attach_cgroup(prog, cgroup_fd);
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_link__update_program to bpf_program__attach_kprobe
        bool ret_bpf_program__autoload_wzgmi = bpf_program__autoload(prog);
        if (ret_bpf_program__autoload_wzgmi == 0){
        	return 0;
        }
        const char fwvjoqcr[1024] = "lvkki";


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__autoload to bpf_program__set_autoattach

        bpf_program__set_autoattach(prog, ret_bpf_program__autoload_wzgmi);

        // End mutation: Producer.APPEND_MUTATOR

        struct bpf_link* ret_bpf_program__attach_kprobe_tdgqn = bpf_program__attach_kprobe(prog, ret_bpf_program__autoload_wzgmi, fwvjoqcr);
        if (ret_bpf_program__attach_kprobe_tdgqn == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}