// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__open at libbpf.c:8407:20 in libbpf.h
// bpf_object__token_fd at libbpf.c:9506:5 in libbpf.h
// bpf_object__open_subskeleton at libbpf.c:14395:5 in libbpf.h
// bpf_object__prepare at libbpf.c:8989:5 in libbpf.h
// bpf_object__find_program_by_name at libbpf.c:4475:1 in libbpf.h
// bpf_object__destroy_subskeleton at libbpf.c:14455:6 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    struct bpf_object *obj = NULL;
    struct bpf_object_subskeleton subskeleton;
    struct bpf_program *prog = NULL;
    char dummy_name[256];
    int ret;

    // Prepare dummy BPF object
    FILE *dummy_file = fopen("./dummy_file", "w");
    if (!dummy_file) {
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    obj = bpf_object__open("./dummy_file");
    if (!obj) {
        return 0;
    }

    // Fuzz bpf_object__token_fd
    int token_fd = bpf_object__token_fd(obj);

    // Fuzz bpf_object__open_subskeleton
    memset(&subskeleton, 0, sizeof(subskeleton));
    subskeleton.sz = sizeof(subskeleton);
    ret = bpf_object__open_subskeleton(&subskeleton);

    // Fuzz bpf_object__prepare
    ret = bpf_object__prepare(obj);

    // Fuzz bpf_object__find_program_by_name
    if (Size > 0 && Size < sizeof(dummy_name)) {
        memcpy(dummy_name, Data, Size);
        dummy_name[Size] = '\0';
        prog = bpf_object__find_program_by_name(obj, dummy_name);
    }

    // Cleanup
    bpf_object__destroy_subskeleton(&subskeleton);
    bpf_object__close(obj);

    return 0;
}