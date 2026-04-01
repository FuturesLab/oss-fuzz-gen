#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test
        int result = bpf_object__prepare(obj);

        // Clean up the bpf_object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__unpin_programs


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__unpin_programs with bpf_object__pin

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__pin with bpf_object__unpin_programs
        int ret_bpf_object__unpin_programs_xzkno = bpf_object__unpin_programs(obj, (const char *)"w");
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_bpf_object__unpin_programs_xzkno < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to bpf_object__set_kversion

    int ret_bpf_object__set_kversion_lnpgs = bpf_object__set_kversion(obj, 0);
    if (ret_bpf_object__set_kversion_lnpgs < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}