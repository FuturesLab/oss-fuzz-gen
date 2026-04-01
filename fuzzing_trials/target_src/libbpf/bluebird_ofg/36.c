#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
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


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_map__get_next_key
        struct bpf_object_subskeleton rknwwmci;
        memset(&rknwwmci, 0, sizeof(rknwwmci));
        int ret_bpf_object__open_subskeleton_ulexz = bpf_object__open_subskeleton(&rknwwmci);
        if (ret_bpf_object__open_subskeleton_ulexz < 0){
        	return 0;
        }
        char jkipsgfp[1024] = "nhetg";

        int ret_bpf_map__get_next_key_fnlez = bpf_map__get_next_key(NULL, jkipsgfp, (void *)obj, (size_t )ret_bpf_object__open_subskeleton_ulexz);
        if (ret_bpf_map__get_next_key_fnlez < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}