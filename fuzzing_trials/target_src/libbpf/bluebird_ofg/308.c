#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_308(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test
        int result = bpf_object__prepare(obj);

        // Clean up the bpf_object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prepare to bpf_object__find_map_by_name

        struct bpf_map* ret_bpf_object__find_map_by_name_kgjvb = bpf_object__find_map_by_name(obj, (const char *)data);
        if (ret_bpf_object__find_map_by_name_kgjvb == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__find_map_by_name to bpf_map__set_initial_value
        unsigned int ret_bpf_object__kversion_aitfe = bpf_object__kversion(obj);
        if (ret_bpf_object__kversion_aitfe < 0){
        	return 0;
        }

        int ret_bpf_map__set_initial_value_kvrci = bpf_map__set_initial_value(ret_bpf_object__find_map_by_name_kgjvb, (const void *)ret_bpf_object__find_map_by_name_kgjvb, (size_t )ret_bpf_object__kversion_aitfe);
        if (ret_bpf_map__set_initial_value_kvrci < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}