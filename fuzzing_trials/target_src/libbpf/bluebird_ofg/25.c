#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bpf_object__open_mem
    struct bpf_object *obj = bpf_object__open_mem((const void *)data, size, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    if (obj != NULL) {
        // Call the function-under-test
        int result = bpf_object__prepare(obj);

        // Clean up the bpf_object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to libbpf_probe_bpf_map_type


        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of libbpf_probe_bpf_map_type
        int ret_libbpf_probe_bpf_map_type_mkdzb = libbpf_probe_bpf_map_type(0, NULL);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret_libbpf_probe_bpf_map_type_mkdzb < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}