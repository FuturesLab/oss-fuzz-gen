#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
        int result = bpf_object__load(obj);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Clean up the bpf_object

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open_mem to bpf_object__prev_map

    struct bpf_map* ret_bpf_object__prev_map_hnjjh = bpf_object__prev_map(obj, NULL);
    if (ret_bpf_object__prev_map_hnjjh == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prev_map to bpf_map__initial_value

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prev_map to bpf_map__set_value_size

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prev_map to bpf_map__set_initial_value

    int ret_bpf_map__set_initial_value_bkmyb = bpf_map__set_initial_value(ret_bpf_object__prev_map_hnjjh, (const void *)"w", 0);
    if (ret_bpf_map__set_initial_value_bkmyb < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    __u32 ret_bpf_map__max_entries_yyshe = bpf_map__max_entries(ret_bpf_object__prev_map_hnjjh);

    int ret_bpf_map__set_value_size_mgivk = bpf_map__set_value_size(ret_bpf_object__prev_map_hnjjh, ret_bpf_map__max_entries_yyshe);
    if (ret_bpf_map__set_value_size_mgivk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_bpf_object__load_gzmbv = bpf_object__load(NULL);
    if (ret_bpf_object__load_gzmbv < 0){
    	return 0;
    }

    void* ret_bpf_map__initial_value_imapt = bpf_map__initial_value(ret_bpf_object__prev_map_hnjjh, (size_t *)&ret_bpf_object__load_gzmbv);
    if (ret_bpf_map__initial_value_imapt == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}