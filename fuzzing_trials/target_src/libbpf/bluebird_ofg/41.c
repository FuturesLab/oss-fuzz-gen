#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__prepare with bpf_object__load
        int result = bpf_object__load(obj);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Clean up the bpf_object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__unpin_programs


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__unpin_programs with bpf_object__pin

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bpf_object__pin

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__load to perf_buffer__new_raw
        struct bpf_object_skeleton vvhxokja;
        memset(&vvhxokja, 0, sizeof(vvhxokja));
        int ret_bpf_object__attach_skeleton_ovztm = bpf_object__attach_skeleton(&vvhxokja);
        if (ret_bpf_object__attach_skeleton_ovztm < 0){
        	return 0;
        }

        struct perf_buffer* ret_perf_buffer__new_raw_vewzd = perf_buffer__new_raw(ret_bpf_object__attach_skeleton_ovztm, 64, NULL, NULL, (void *)obj, NULL);
        if (ret_perf_buffer__new_raw_vewzd == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        int ret_bpf_object__unpin_programs_xzkno = bpf_object__pin(obj, NULL);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_bpf_object__unpin_programs_xzkno < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}