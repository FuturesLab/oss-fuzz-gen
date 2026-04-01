#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__log_buf
    size_t ysxdsomx = -1;


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_perf_event
    int ret_bpf_object__load_wrium = bpf_object__load(obj);
    if (ret_bpf_object__load_wrium < 0){
    	return 0;
    }

    struct bpf_link* ret_bpf_program__attach_perf_event_itzfo = bpf_program__attach_perf_event(prog, ret_bpf_object__load_wrium);
    if (ret_bpf_program__attach_perf_event_itzfo == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__log_buf
    size_t dfhqqhmz = 0;
    const char* ret_bpf_program__log_buf_fzaop = bpf_program__log_buf(prog, &dfhqqhmz);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bpf_program__log_buf_fzaop == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int result = bpf_program__set_attach_target(prog, 0, target);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to perf_buffer__buffer
    struct bpf_object* ret_bpf_object__open_xowhv = bpf_object__open((const char *)"w");
    if (ret_bpf_object__open_xowhv == NULL){
    	return 0;
    }
    size_t wyxitjxc = -1;


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open to libbpf_probe_bpf_prog_type

    int ret_libbpf_probe_bpf_prog_type_pxscl = libbpf_probe_bpf_prog_type(0, (const void *)ret_bpf_object__open_xowhv);
    if (ret_libbpf_probe_bpf_prog_type_pxscl < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_perf_buffer__buffer_wjhdx = perf_buffer__buffer(NULL, result, (void **)&ret_bpf_object__open_xowhv, &wyxitjxc);
    if (ret_perf_buffer__buffer_wjhdx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from perf_buffer__buffer to bpf_map__initial_value
    struct bpf_map* ret_bpf_map__inner_map_wnahb = bpf_map__inner_map(NULL);
    if (ret_bpf_map__inner_map_wnahb == NULL){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_map__initial_value

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_map__inner_map to bpf_map__set_key_size
    __u32 ret_libbpf_minor_version_pyyav = libbpf_minor_version();

    int ret_bpf_map__set_key_size_ponaz = bpf_map__set_key_size(ret_bpf_map__inner_map_wnahb, ret_libbpf_minor_version_pyyav);
    if (ret_bpf_map__set_key_size_ponaz < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    void* ret_bpf_map__initial_value_qudhf = bpf_map__initial_value(ret_bpf_map__inner_map_wnahb, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bpf_map__initial_value_qudhf == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);
    free(target);

    return 0;
}