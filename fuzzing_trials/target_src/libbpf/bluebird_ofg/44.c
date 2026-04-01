#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bpf_object__open_mem
    struct bpf_object *obj = bpf_object__open_mem((const void *)data, size, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    if (obj != NULL) {
        // Call the function-under-test

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
        int result = bpf_object__load(obj);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Clean up the bpf_object
        bpf_object__close(obj);
    }

    return 0;
}