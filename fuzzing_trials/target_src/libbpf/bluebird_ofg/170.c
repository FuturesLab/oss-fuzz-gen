#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);

    if (obj != NULL) {
        // Call the function-under-test
        int result = bpf_object__prepare(obj);

        // Clean up the bpf_object

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__token_fd


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__prepare to bpf_object__btf_fd

        int ret_bpf_object__btf_fd_qbqei = bpf_object__btf_fd(obj);
        if (ret_bpf_object__btf_fd_qbqei < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        int ret_bpf_object__token_fd_zcczy = bpf_object__token_fd(obj);
        if (ret_bpf_object__token_fd_zcczy < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bpf_object__close(obj);
    }

    return 0;
}