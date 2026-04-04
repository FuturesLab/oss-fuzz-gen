#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_364(const uint8_t *data, size_t size) {
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
    prog = bpf_object__prev_program(obj, NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (!prog) {
        bpf_object__close(obj);
        return 0;
    }

    // Use the first byte of data to determine the attach_type
    attach_type = (int)data[0];

    // Allocate memory for the target string and copy data into it

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_xdp
    int ret_bpf_object__load_jqurq = bpf_object__load(obj);
    if (ret_bpf_object__load_jqurq < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_program__attach_xdp with bpf_program__attach_perf_event
    struct bpf_link* ret_bpf_program__attach_xdp_vvvez = bpf_program__attach_perf_event(prog, ret_bpf_object__load_jqurq);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_program__attach_xdp_vvvez == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__attach_perf_event to bpf_link__pin_path

    const char* ret_bpf_link__pin_path_fiawg = bpf_link__pin_path(ret_bpf_program__attach_xdp_vvvez);
    if (ret_bpf_link__pin_path_fiawg == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    target = (char *)malloc(size);
    if (target == NULL) {
        bpf_object__close(obj);
        return 0;
    }
    memcpy(target, data + 1, size - 1);
    target[size - 1] = '\0'; // Ensure null-termination

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_program__set_attach_target
    bpf_program__set_attach_target(prog, 0, target);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    free(target);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__kversion

        unsigned int ret_bpf_object__kversion_gmwuy = bpf_object__kversion(obj);
        if (ret_bpf_object__kversion_gmwuy < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__gen_loader
        struct gen_loader_opts rypdamik;
        memset(&rypdamik, 0, sizeof(rypdamik));

        int ret_bpf_object__gen_loader_aoohn = bpf_object__gen_loader(obj, &rypdamik);
        if (ret_bpf_object__gen_loader_aoohn < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__find_program_by_name

        struct bpf_program* ret_bpf_object__find_program_by_name_kjehg = bpf_object__find_program_by_name(obj, (const char *)"w");
        if (ret_bpf_object__find_program_by_name_kjehg == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}