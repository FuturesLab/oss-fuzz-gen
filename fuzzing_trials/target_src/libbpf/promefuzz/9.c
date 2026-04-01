// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__open_mem at libbpf.c:8413:1 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
// bpf_object__pin at libbpf.c:9371:5 in libbpf.h
// bpf_object__detach_skeleton at libbpf.c:14572:6 in libbpf.h
// bpf_object__load_skeleton at libbpf.c:14465:5 in libbpf.h
// bpf_object__open_skeleton at libbpf.c:14365:5 in libbpf.h
// bpf_object__unpin_programs at libbpf.c:9348:5 in libbpf.h
// bpf_object__attach_skeleton at libbpf.c:14491:5 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <libbpf.h>

static struct bpf_object_skeleton *create_dummy_skeleton() {
    struct bpf_object_skeleton *skeleton = malloc(sizeof(struct bpf_object_skeleton));
    if (!skeleton)
        return NULL;

    memset(skeleton, 0, sizeof(struct bpf_object_skeleton));
    return skeleton;
}

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1)
        return 0;

    struct bpf_object_skeleton *skeleton = create_dummy_skeleton();
    struct bpf_object *object = bpf_object__open_mem(Data, Size, NULL);
    if (!skeleton || !object) {
        free(skeleton);
        if (object)
            bpf_object__close(object);
        return 0;
    }

    // Create a dummy file for testing
    int fd = open("./dummy_file", O_RDWR | O_CREAT, 0600);
    if (fd < 0) {
        free(skeleton);
        bpf_object__close(object);
        return 0;
    }
    write(fd, Data, Size);
    close(fd);

    // Fuzz bpf_object__pin
    char path[256];
    snprintf(path, sizeof(path), "./dummy_file_%zu", Size);
    bpf_object__pin(object, path);

    // Fuzz bpf_object__detach_skeleton
    bpf_object__detach_skeleton(skeleton);

    // Fuzz bpf_object__load_skeleton
    bpf_object__load_skeleton(skeleton);

    // Fuzz bpf_object__open_skeleton
    struct bpf_object_open_opts opts = { .sz = sizeof(opts) };
    bpf_object__open_skeleton(skeleton, &opts);

    // Fuzz bpf_object__unpin_programs
    bpf_object__unpin_programs(object, path);

    // Fuzz bpf_object__attach_skeleton
    bpf_object__attach_skeleton(skeleton);

    // Cleanup
    free(skeleton);
    bpf_object__close(object);
    unlink("./dummy_file");
    unlink(path);

    return 0;
}