// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__open_skeleton at libbpf.c:14365:5 in libbpf.h
// bpf_object__load_skeleton at libbpf.c:14465:5 in libbpf.h
// bpf_object__attach_skeleton at libbpf.c:14491:5 in libbpf.h
// bpf_object__unpin_programs at libbpf.c:9348:5 in libbpf.h
// bpf_object__detach_skeleton at libbpf.c:14572:6 in libbpf.h
// bpf_object__destroy_skeleton at libbpf.c:14598:6 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>

static int create_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file)
        return -1;
    fwrite(Data, 1, Size, file);
    fclose(file);
    return 0;
}

static struct bpf_object_skeleton* init_skeleton(const uint8_t *Data, size_t Size) {
    struct bpf_object_skeleton *skeleton = malloc(sizeof(struct bpf_object_skeleton));
    if (!skeleton)
        return NULL;
    memset(skeleton, 0, sizeof(*skeleton));
    skeleton->sz = sizeof(*skeleton);
    skeleton->name = "dummy_skeleton";
    skeleton->data = Data;
    skeleton->data_sz = Size;
    return skeleton;
}

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size == 0)
        return 0;

    struct bpf_object_skeleton *skeleton = init_skeleton(Data, Size);
    if (!skeleton)
        return 0;

    struct bpf_object_open_opts opts = {
        .sz = sizeof(struct bpf_object_open_opts),
        .object_name = "fuzz_object",
    };

    int ret = bpf_object__open_skeleton(skeleton, &opts);
    if (ret >= 0) {
        bpf_object__load_skeleton(skeleton);
        bpf_object__attach_skeleton(skeleton);
        bpf_object__unpin_programs(*skeleton->obj, "./dummy_file");
        bpf_object__detach_skeleton(skeleton);
    }

    // bpf_object__destroy_skeleton already frees the skeleton
    // so we should not free it again
    bpf_object__destroy_skeleton(skeleton);

    return 0;
}