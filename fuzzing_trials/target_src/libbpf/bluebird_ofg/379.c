#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_379(const uint8_t *data, size_t size) {
    struct bpf_program *prog;
    int attach_type;
    char *target;
    struct bpf_object *obj;

    // Ensure data size is sufficient for creating a string
    if (size < 1) {
        return 0;
    }

    // Load a dummy BPF object to initialize a bpf_program
    obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0;
    }

    // Get the first program from the BPF object

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__next_program with bpf_object__prev_program

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prev_program with bpf_object__next_program
    prog = bpf_object__next_program(obj, NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (!prog) {
        bpf_object__close(obj);
        return 0;
    }

    // Use the first byte of data to determine the attach_type
    attach_type = (int)data[0];

    // Allocate memory for the target string and copy data into it
    target = (char *)malloc(size);
    if (target == NULL) {
        bpf_object__close(obj);
        return 0;
    }
    memcpy(target, data + 1, size - 1);
    target[size - 1] = '\0'; // Ensure null-termination

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__set_attach_target

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of bpf_program__set_attach_target
    bpf_program__set_attach_target(prog, 0, (const char *)"r");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to perf_buffer__buffer
    int ret_bpf_map__fd_mtroc = bpf_map__fd(NULL);
    if (ret_bpf_map__fd_mtroc < 0){
    	return 0;
    }
    size_t dwomspih = size;


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_map__fd to bpf_program__attach_netkit

    struct bpf_link* ret_bpf_program__attach_netkit_uecfi = bpf_program__attach_netkit(prog, ret_bpf_map__fd_mtroc, NULL);
    if (ret_bpf_program__attach_netkit_uecfi == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_perf_buffer__buffer_ykrxv = perf_buffer__buffer(NULL, ret_bpf_map__fd_mtroc, (void **)&prog, &dwomspih);
    if (ret_perf_buffer__buffer_ykrxv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(target);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__kversion

        unsigned int ret_bpf_object__kversion_gmwuy = bpf_object__kversion(obj);
        if (ret_bpf_object__kversion_gmwuy < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__find_map_by_name
        const char yehnfiep[1024] = "byxoy";

        struct bpf_map* ret_bpf_object__find_map_by_name_thyuw = bpf_object__find_map_by_name(obj, yehnfiep);
        if (ret_bpf_object__find_map_by_name_thyuw == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}