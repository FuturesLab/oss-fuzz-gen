#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to perf_buffer__new


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of perf_buffer__new
    struct perf_buffer* ret_perf_buffer__new_pjlxb = perf_buffer__new(64, 1, NULL, NULL, (void *)obj, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_perf_buffer__new_pjlxb == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        return 0;
    }

    // Use the first byte of data to determine the attach_type
    attach_type = (int)data[0];

    // Allocate memory for the target string and copy data into it

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_kprobe

    struct bpf_link* ret_bpf_program__attach_kprobe_kelcs = bpf_program__attach_kprobe(prog, 1, NULL);
    if (ret_bpf_program__attach_kprobe_kelcs == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__attach_kprobe to perf_buffer__buffer
    int ret_bpf_link__unpin_robfr = bpf_link__unpin(ret_bpf_program__attach_kprobe_kelcs);
    if (ret_bpf_link__unpin_robfr < 0){
    	return 0;
    }

    int ret_perf_buffer__buffer_gkbbz = perf_buffer__buffer(ret_perf_buffer__new_pjlxb, -1, (void **)&ret_bpf_program__attach_kprobe_kelcs, (size_t *)&ret_bpf_link__unpin_robfr);
    if (ret_perf_buffer__buffer_gkbbz < 0){
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__pin
    const char xqjssnmx[1024] = "kkyql";

    int ret_bpf_object__pin_erezz = bpf_object__pin(obj, xqjssnmx);
    if (ret_bpf_object__pin_erezz < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}