#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_247(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);
    if (obj == NULL) {
        return 0; // If object creation fails, exit early
    }

    // Call the function-under-test
    int result = bpf_object__prepare(obj);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__set_kversion
    __u32 ret_bpf_map__btf_key_type_id_simny = bpf_map__btf_key_type_id(NULL);

    int ret_bpf_object__set_kversion_mnjtg = bpf_object__set_kversion(obj, ret_bpf_map__btf_key_type_id_simny);
    if (ret_bpf_object__set_kversion_mnjtg < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);

    return 0;
}