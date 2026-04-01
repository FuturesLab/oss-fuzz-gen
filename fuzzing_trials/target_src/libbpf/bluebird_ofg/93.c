#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Ensure the data is null-terminated to safely use it as a string
    char *target = (char *)malloc(size + 1);
    if (!target) {
        return 0;
    }
    memcpy(target, data, size);
    target[size] = '\0';

    // Initialize libbpf
    libbpf_set_strict_mode(LIBBPF_STRICT_ALL);

    // Create a new BPF program object
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        free(target);
        return 0;
    }

    struct bpf_program *prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        free(target);
        return 0;
    }

    int attach_type = (int)data[0]; // Use the first byte of data as an integer

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__set_attach_target

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__set_insns
    struct bpf_insn xctakrrd;
    memset(&xctakrrd, 0, sizeof(xctakrrd));

    int ret_bpf_program__set_insns_ddmly = bpf_program__set_insns(prog, &xctakrrd, 0);
    if (ret_bpf_program__set_insns_ddmly < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__set_attach_target
    int result = bpf_program__set_attach_target(prog, size, target);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to perf_buffer__buffer

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to bpf_program__attach_lsm


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_program__attach_lsm with bpf_program__attach

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to bpf_program__attach_ksyscall


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to perf_buffer__new
    int ret_bpf_link__destroy_tosvl = bpf_link__destroy(NULL);
    if (ret_bpf_link__destroy_tosvl < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of perf_buffer__new
    struct perf_buffer* ret_perf_buffer__new_anang = perf_buffer__new(1, 64, NULL, NULL, (void *)prog, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_perf_buffer__new_anang == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    struct bpf_link* ret_bpf_program__attach_ksyscall_lwwzh = bpf_program__attach_ksyscall(prog, (const char *)data, NULL);
    if (ret_bpf_program__attach_ksyscall_lwwzh == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    struct bpf_link* ret_bpf_program__attach_lsm_wtzsk = bpf_program__attach(prog);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_program__attach_lsm_wtzsk == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bpf_object__open
    const char iadkchzn[1024] = "ulqdd";
    struct bpf_object* ret_bpf_object__open_xowhv = bpf_object__open(iadkchzn);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bpf_object__open_xowhv == NULL){
    	return 0;
    }
    size_t wyxitjxc = -1;

    int ret_perf_buffer__buffer_wjhdx = perf_buffer__buffer(NULL, result, (void **)&ret_bpf_object__open_xowhv, &wyxitjxc);
    if (ret_perf_buffer__buffer_wjhdx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to libbpf_probe_bpf_map_type

    int ret_libbpf_probe_bpf_map_type_fnzfa = libbpf_probe_bpf_map_type(0, (const void *)obj);
    if (ret_libbpf_probe_bpf_map_type_fnzfa < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from libbpf_probe_bpf_map_type to libbpf_strerror
    struct bpf_object_skeleton pztodtwp;
    memset(&pztodtwp, 0, sizeof(pztodtwp));
    int ret_bpf_object__load_skeleton_xlwrv = bpf_object__load_skeleton(&pztodtwp);
    if (ret_bpf_object__load_skeleton_xlwrv < 0){
    	return 0;
    }

    int ret_libbpf_strerror_kekhc = libbpf_strerror(ret_bpf_object__load_skeleton_xlwrv, (char *)"r", (size_t )ret_libbpf_probe_bpf_map_type_fnzfa);
    if (ret_libbpf_strerror_kekhc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(target);

    return 0;
}