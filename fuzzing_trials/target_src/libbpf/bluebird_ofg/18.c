#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
        int result = bpf_object__load(obj);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Clean up the bpf_object

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to bpf_object__find_program_by_name

    struct bpf_program* ret_bpf_object__find_program_by_name_xhakz = bpf_object__find_program_by_name(obj, (const char *)data);
    if (ret_bpf_object__find_program_by_name_xhakz == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}