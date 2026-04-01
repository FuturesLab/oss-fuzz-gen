// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__open_mem at libbpf.c:8413:1 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
// bpf_object__load at libbpf.c:8994:5 in libbpf.h
// bpf_object__pin at libbpf.c:9371:5 in libbpf.h
// bpf_object__open_skeleton at libbpf.c:14365:5 in libbpf.h
// bpf_object__token_fd at libbpf.c:9506:5 in libbpf.h
// bpf_object__prepare at libbpf.c:8989:5 in libbpf.h
// bpf_object__gen_loader at libbpf.c:9531:5 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libbpf.h>

static struct bpf_object *open_bpf_object(const uint8_t *data, size_t size) {
    struct bpf_object_open_opts opts = {
        .sz = sizeof(struct bpf_object_open_opts),
        .object_name = "fuzz_object",
    };
    struct bpf_object *obj = bpf_object__open_mem(data, size, &opts);
    return obj;
}

static void cleanup_bpf_object(struct bpf_object *obj) {
    if (obj) {
        bpf_object__close(obj);
    }
}

int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct bpf_object *obj = open_bpf_object(Data, Size);
    if (!obj) {
        return 0;
    }

    // Test bpf_object__load
    int ret = bpf_object__load(obj);
    if (ret < 0) {
        fprintf(stderr, "bpf_object__load failed: %s\n", strerror(errno));
    }

    // Test bpf_object__pin
    ret = bpf_object__pin(obj, "./dummy_file");
    if (ret < 0) {
        fprintf(stderr, "bpf_object__pin failed: %s\n", strerror(errno));
    }

    // Test bpf_object__open_skeleton
    struct bpf_object_skeleton skeleton = { .sz = sizeof(skeleton) };
    ret = bpf_object__open_skeleton(&skeleton, NULL);
    if (ret < 0) {
        fprintf(stderr, "bpf_object__open_skeleton failed: %s\n", strerror(errno));
    }

    // Test bpf_object__token_fd
    int fd = bpf_object__token_fd(obj);
    if (fd == -1) {
        fprintf(stderr, "bpf_object__token_fd returned -1\n");
    }

    // Test bpf_object__prepare
    ret = bpf_object__prepare(obj);
    if (ret < 0) {
        fprintf(stderr, "bpf_object__prepare failed: %s\n", strerror(errno));
    }

    // Test bpf_object__gen_loader
    struct gen_loader_opts opts = { .sz = sizeof(opts) };
    ret = bpf_object__gen_loader(obj, &opts);
    if (ret < 0) {
        fprintf(stderr, "bpf_object__gen_loader failed: %s\n", strerror(errno));
    }

    cleanup_bpf_object(obj);
    return 0;
}