#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prev_map to bpf_map__pin


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_map__pin with bpf_map__set_pin_path

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_map__set_pin_path
    const char hqsgsila[1024] = "rymen";
    int ret_bpf_map__pin_fugcc = bpf_map__set_pin_path(ret_bpf_object__prev_map_hnjjh, hqsgsila);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_bpf_map__pin_fugcc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_bpf_link__destroy_zbhjj = bpf_link__destroy(NULL);
    if (ret_bpf_link__destroy_zbhjj < 0){
    	return 0;
    }

    void* ret_bpf_map__initial_value_lbtqs = bpf_map__initial_value(ret_bpf_object__prev_map_hnjjh, (size_t *)&ret_bpf_link__destroy_zbhjj);
    if (ret_bpf_map__initial_value_lbtqs == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}