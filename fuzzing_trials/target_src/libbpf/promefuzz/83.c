// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
// bpf_object__open at libbpf.c:8407:20 in libbpf.h
// bpf_object__set_kversion at libbpf.c:9521:5 in libbpf.h
// bpf_object__btf at libbpf.c:9511:13 in libbpf.h
// bpf_object__prepare at libbpf.c:8989:5 in libbpf.h
// bpf_object__open_mem at libbpf.c:8413:1 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
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
#include <libbpf.h>

static void clean_up(struct bpf_object *obj) {
    if (obj) {
        bpf_object__close(obj);
    }
}

int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
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
    bpf_object__prepare(obj);

    // Fuzz bpf_object__open_mem
    struct bpf_object *mem_obj = bpf_object__open_mem(Data, Size, NULL);
    if (mem_obj) {
        bpf_object__close(mem_obj);
    }

    // Cleanup
    clean_up(obj);

    // Remove dummy file
    remove(dummy_path);

    return 0;
}