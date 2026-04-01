#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
        int result = bpf_object__load(obj);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Clean up the bpf_object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__unpin_programs


        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_object__unpin_programs
        int ret_bpf_object__unpin_programs_usdfq = bpf_object__unpin_programs(obj, (const char *)"r");
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret_bpf_object__unpin_programs_usdfq < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}