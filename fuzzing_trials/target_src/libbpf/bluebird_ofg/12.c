#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to bpf_object__load

    int ret_bpf_object__load_nnecp = bpf_object__load(obj);
    if (ret_bpf_object__load_nnecp < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_kprobe


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prev_program to bpf_program__attach_usdt

    struct bpf_link* ret_bpf_program__attach_usdt_qidod = bpf_program__attach_usdt(prog, 0, (const char *)"r", NULL, (const char *)"r", NULL);
    if (ret_bpf_program__attach_usdt_qidod == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    struct bpf_link* ret_bpf_program__attach_kprobe_kelcs = bpf_program__attach_kprobe(prog, 1, NULL);
    if (ret_bpf_program__attach_kprobe_kelcs == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__attach_kprobe to bpf_map__set_initial_value
    struct bpf_map* ret_bpf_map__inner_map_dbltq = bpf_map__inner_map(NULL);
    if (ret_bpf_map__inner_map_dbltq == NULL){
    	return 0;
    }

    int ret_bpf_map__set_initial_value_gxxkh = bpf_map__set_initial_value(ret_bpf_map__inner_map_dbltq, (const void *)ret_bpf_program__attach_kprobe_kelcs, 0);
    if (ret_bpf_map__set_initial_value_gxxkh < 0){
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
    bpf_program__set_attach_target(prog, attach_type, target);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to bpf_program__attach_iter


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__set_attach_target to bpf_object__prev_program
    int ret_bpf_object__prepare_mroys = bpf_object__prepare(obj);
    if (ret_bpf_object__prepare_mroys < 0){
    	return 0;
    }

    struct bpf_program* ret_bpf_object__prev_program_thwmy = bpf_object__prev_program(obj, prog);
    if (ret_bpf_object__prev_program_thwmy == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    struct bpf_link* ret_bpf_program__attach_iter_ozpnh = bpf_program__attach_iter(prog, NULL);
    if (ret_bpf_program__attach_iter_ozpnh == NULL){
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

    bpf_object__close(obj);

    return 0;
}