#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libbpf.h"

static void clean_up(struct bpf_object *obj) {
    if (obj) {
        bpf_object__close(obj);
    }
}

int LLVMFuzzerTestOneInput_125(const uint8_t *Data, size_t Size) {
    if (Size < 4) {
        return 0;
    }

    // Create a dummy BPF object file
    const char *dummy_path = "./dummy_file";
    FILE *file = fopen(dummy_path, "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the BPF object
    struct bpf_object *obj = bpf_object__open(dummy_path);
    if (!obj) {
        return 0;
    }

    // Fuzz bpf_object__set_kversion
    __u32 kern_version = *(const __u32 *)Data;
    bpf_object__set_kversion(obj, kern_version);

    // Fuzz bpf_object__btf
    struct btf *btf = bpf_object__btf(obj);

    // Fuzz bpf_object__prepare

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__btf to perf_buffer__new

    struct perf_buffer* ret_perf_buffer__new_toxsy = perf_buffer__new(0, 64, NULL, NULL, (void *)btf, NULL);
    if (ret_perf_buffer__new_toxsy == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from perf_buffer__new to bpf_object__find_map_by_name

    struct bpf_map* ret_bpf_object__find_map_by_name_vpjlj = bpf_object__find_map_by_name(NULL, btf);
    if (ret_bpf_object__find_map_by_name_vpjlj == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__prepare(obj);

    // Fuzz bpf_object__open_mem
    struct bpf_object *mem_obj = bpf_object__open_mem(Data, Size, NULL);
    if (mem_obj) {

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bpf_object__close
        bpf_object__close(obj);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


    }

    // Cleanup
    clean_up(obj);

    // Remove dummy file

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__close to bpf_object__open_mem
        struct bpf_object_skeleton hzwojhdd;
        memset(&hzwojhdd, 0, sizeof(hzwojhdd));

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bpf_object__attach_skeleton with bpf_object__load_skeleton
        int ret_bpf_object__attach_skeleton_vabma = bpf_object__load_skeleton(&hzwojhdd);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_bpf_object__attach_skeleton_vabma < 0){
        	return 0;
        }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__attach_skeleton to bpf_program__attach_freplace

        struct bpf_link* ret_bpf_program__attach_freplace_gtvum = bpf_program__attach_freplace(NULL, ret_bpf_object__attach_skeleton_vabma, NULL);
        if (ret_bpf_program__attach_freplace_gtvum == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        struct bpf_object* ret_bpf_object__open_mem_jbgbp = bpf_object__open_mem((const void *)mem_obj, (size_t )ret_bpf_object__attach_skeleton_vabma, NULL);
        if (ret_bpf_object__open_mem_jbgbp == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    remove(dummy_path);

    return 0;
}