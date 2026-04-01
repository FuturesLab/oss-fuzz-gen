#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
        int result = bpf_object__load(obj);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Clean up the bpf_object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__unpin_programs


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__unpin_programs with bpf_object__pin
        int ret_bpf_object__unpin_programs_xzkno = bpf_object__pin(obj, (const char *)"w");
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_bpf_object__unpin_programs_xzkno < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to perf_buffer__buffer
    int ret_libbpf_unregister_prog_handler_gnlme = libbpf_unregister_prog_handler(64);
    if (ret_libbpf_unregister_prog_handler_gnlme < 0){
    	return 0;
    }
    size_t vjunymjy = 0;

    int ret_perf_buffer__buffer_qpfcd = perf_buffer__buffer(NULL, ret_libbpf_unregister_prog_handler_gnlme, (void **)&obj, &vjunymjy);
    if (ret_perf_buffer__buffer_qpfcd < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}