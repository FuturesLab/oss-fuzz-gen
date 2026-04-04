#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_394(const uint8_t *data, size_t size) {
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
    prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        return 0;
    }

    // Use the first byte of data to determine the attach_type
    attach_type = (int)data[0];

    // Allocate memory for the target string and copy data into it

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_kprobe


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of bpf_program__attach_kprobe
    const char xrqrpvcu[1024] = "inhhj";

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__next_program to bpf_program__attach_uprobe
    int ret_libbpf_num_possible_cpus_bdvpd = libbpf_num_possible_cpus();
    if (ret_libbpf_num_possible_cpus_bdvpd < 0){
    	return 0;
    }

    struct bpf_link* ret_bpf_program__attach_uprobe_yecvx = bpf_program__attach_uprobe(prog, 0, 0, (const char *)data, (size_t )ret_libbpf_num_possible_cpus_bdvpd);
    if (ret_bpf_program__attach_uprobe_yecvx == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    struct bpf_link* ret_bpf_program__attach_kprobe_kelcs = bpf_program__attach_kprobe(prog, 1, xrqrpvcu);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bpf_program__attach_kprobe_kelcs == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__attach_kprobe to bpf_map__get_next_key
    int ret_bpf_program__fd_pgwtf = bpf_program__fd(prog);
    if (ret_bpf_program__fd_pgwtf < 0){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__fd to bpf_map__lookup_and_delete_elem
    struct bpf_map* ret_bpf_map__inner_map_tixcd = bpf_map__inner_map(NULL);
    if (ret_bpf_map__inner_map_tixcd == NULL){
    	return 0;
    }
    int ret_bpf_link__unpin_wzbyt = bpf_link__unpin(ret_bpf_program__attach_kprobe_kelcs);
    if (ret_bpf_link__unpin_wzbyt < 0){
    	return 0;
    }
    size_t ret_perf_buffer__buffer_cnt_pyydm = perf_buffer__buffer_cnt(NULL);
    if (ret_perf_buffer__buffer_cnt_pyydm < 0){
    	return 0;
    }

    int ret_bpf_map__lookup_and_delete_elem_ecnes = bpf_map__lookup_and_delete_elem(ret_bpf_map__inner_map_tixcd, (const void *)data, (size_t )ret_bpf_program__fd_pgwtf, (void *)ret_bpf_program__attach_kprobe_kelcs, ret_perf_buffer__buffer_cnt_pyydm, 0);
    if (ret_bpf_map__lookup_and_delete_elem_ecnes < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_bpf_map__get_next_key_bkptd = bpf_map__get_next_key(NULL, (const void *)ret_bpf_program__attach_kprobe_kelcs, (void *)obj, (size_t )ret_bpf_program__fd_pgwtf);
    if (ret_bpf_map__get_next_key_bkptd < 0){
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


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__kversion to bpf_program__attach_perf_event

        struct bpf_link* ret_bpf_program__attach_perf_event_odjkq = bpf_program__attach_perf_event(NULL, (int )ret_bpf_object__kversion_gmwuy);
        if (ret_bpf_program__attach_perf_event_odjkq == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_program__attach_perf_event to bpf_map__lookup_elem
        struct bpf_object_skeleton zocthunm;
        memset(&zocthunm, 0, sizeof(zocthunm));
        int ret_bpf_object__load_skeleton_nullf = bpf_object__load_skeleton(&zocthunm);
        if (ret_bpf_object__load_skeleton_nullf < 0){
        	return 0;
        }
        __u64 ret_bpf_map__map_extra_fvnko = bpf_map__map_extra(ret_bpf_map__inner_map_tixcd);

        int ret_bpf_map__lookup_elem_qlguw = bpf_map__lookup_elem(ret_bpf_map__inner_map_tixcd, (const void *)ret_bpf_program__attach_perf_event_odjkq, (size_t )ret_bpf_object__load_skeleton_nullf, (void *)obj, (size_t )ret_bpf_object__kversion_gmwuy, ret_bpf_map__map_extra_fvnko);
        if (ret_bpf_map__lookup_elem_qlguw < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}