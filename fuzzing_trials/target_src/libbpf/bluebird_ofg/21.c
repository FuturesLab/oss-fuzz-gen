#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test
        int result = bpf_object__prepare(obj);

        // Clean up the bpf_object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prepare to bpf_map__set_initial_value
        struct bpf_link* ret_bpf_link__open_izusm = bpf_link__open(NULL);
        if (ret_bpf_link__open_izusm == NULL){
        	return 0;
        }

        int ret_bpf_map__set_initial_value_mqseh = bpf_map__set_initial_value(NULL, (const void *)ret_bpf_link__open_izusm, (size_t )result);
        if (ret_bpf_map__set_initial_value_mqseh < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}