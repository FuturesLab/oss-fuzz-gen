// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__open at libbpf.c:8407:20 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
// bpf_object__set_kversion at libbpf.c:9521:5 in libbpf.h
// bpf_object__btf at libbpf.c:9511:13 in libbpf.h
// bpf_object__load_skeleton at libbpf.c:14465:5 in libbpf.h
// bpf_object__prepare at libbpf.c:8989:5 in libbpf.h
// bpf_object__kversion at libbpf.c:9501:14 in libbpf.h
// bpf_object__attach_skeleton at libbpf.c:14491:5 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>

static struct bpf_object *create_dummy_bpf_object() {
    // We cannot allocate memory for an incomplete type directly.
    // Instead, we assume there is a function to create a bpf_object.
    struct bpf_object *obj = bpf_object__open("./dummy_file");
    if (!obj) {
        fprintf(stderr, "Failed to create bpf_object\n");
    }
    return obj;
}

static struct bpf_object_skeleton *create_dummy_bpf_object_skeleton() {
    struct bpf_object_skeleton *skeleton = (struct bpf_object_skeleton *)malloc(sizeof(struct bpf_object_skeleton));
    if (!skeleton) {
        fprintf(stderr, "Failed to allocate memory for bpf_object_skeleton\n");
        return NULL;
    }
    memset(skeleton, 0, sizeof(*skeleton));
    return skeleton;
}

int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(__u32)) return 0;

    struct bpf_object *obj = create_dummy_bpf_object();
    if (!obj) return 0;

    struct bpf_object_skeleton *skeleton = create_dummy_bpf_object_skeleton();
    if (!skeleton) {
        bpf_object__close(obj);
        return 0;
    }

    __u32 kern_version = *(const __u32 *)Data;

    // Fuzz bpf_object__set_kversion
    int ret = bpf_object__set_kversion(obj, kern_version);
    if (ret < 0) {
        fprintf(stderr, "bpf_object__set_kversion failed: %s\n", strerror(-ret));
    }

    // Fuzz bpf_object__btf
    struct btf *btf_info = bpf_object__btf(obj);
    if (!btf_info) {
        fprintf(stderr, "bpf_object__btf returned NULL\n");
    }

    // Fuzz bpf_object__load_skeleton
    ret = bpf_object__load_skeleton(skeleton);
    if (ret < 0) {
        fprintf(stderr, "bpf_object__load_skeleton failed: %s\n", strerror(-ret));
    }

    // Fuzz bpf_object__prepare
    ret = bpf_object__prepare(obj);
    if (ret < 0) {
        fprintf(stderr, "bpf_object__prepare failed: %s\n", strerror(-ret));
    }

    // Fuzz bpf_object__kversion
    unsigned int version = bpf_object__kversion(obj);
    printf("Kernel version: %u\n", version);

    // Fuzz bpf_object__attach_skeleton
    ret = bpf_object__attach_skeleton(skeleton);
    if (ret < 0) {
        fprintf(stderr, "bpf_object__attach_skeleton failed: %s\n", strerror(-ret));
    }

    bpf_object__close(obj);
    free(skeleton);
    return 0;
}