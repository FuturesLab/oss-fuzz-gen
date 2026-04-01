// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__next_map at libbpf.c:10880:1 in libbpf.h
// bpf_map__type at libbpf.c:10573:19 in libbpf.h
// bpf_map__set_value_size at libbpf.c:10714:5 in libbpf.h
// bpf_map__set_type at libbpf.c:10578:5 in libbpf.h
// bpf_map__fd at libbpf.c:10538:5 in libbpf.h
// bpf_map__get_next_key at libbpf.c:11044:5 in libbpf.h
// bpf_map__set_key_size at libbpf.c:10630:5 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

static struct bpf_map *create_dummy_bpf_map() {
    // Create a dummy bpf_map with minimal initialization
    struct bpf_map *map = bpf_object__next_map(NULL, NULL);
    return map;
}

static void cleanup_bpf_map(struct bpf_map *map) {
    // No dynamic allocation was done for bpf_map, so no cleanup is necessary
}

int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(__u32) + 1) {
        return 0;
    }

    struct bpf_map *map = create_dummy_bpf_map();
    if (!map) {
        return 0;
    }

    // Fuzzing bpf_map__type
    enum bpf_map_type map_type = bpf_map__type(map);

    // Fuzzing bpf_map__set_value_size
    __u32 new_value_size = *(const __u32 *)Data;
    int ret = bpf_map__set_value_size(map, new_value_size);
    if (ret < 0) {
        // Handle error if needed
    }

    // Fuzzing bpf_map__set_type
    enum bpf_map_type new_map_type = (enum bpf_map_type)(Data[0] % BPF_MAP_TYPE_TASK_STORAGE);
    ret = bpf_map__set_type(map, new_map_type);
    if (ret < 0) {
        // Handle error if needed
    }

    // Fuzzing bpf_map__fd
    int fd = bpf_map__fd(map);
    if (fd >= 0) {
        close(fd);
    }

    // Fuzzing bpf_map__get_next_key
    uint8_t key_buffer[64];
    const void *cur_key = NULL;
    void *next_key = key_buffer;
    size_t key_sz = sizeof(key_buffer);
    ret = bpf_map__get_next_key(map, cur_key, next_key, key_sz);
    if (ret < 0 && ret != -ENOENT) {
        // Handle error if needed
    }

    // Fuzzing bpf_map__set_key_size
    __u32 new_key_size = *(const __u32 *)(Data + 1);
    ret = bpf_map__set_key_size(map, new_key_size);
    if (ret < 0) {
        // Handle error if needed
    }

    cleanup_bpf_map(map);
    return 0;
}