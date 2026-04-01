// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_map__get_next_key at libbpf.c:11044:5 in libbpf.h
// bpf_map__set_key_size at libbpf.c:10630:5 in libbpf.h
// bpf_map__lookup_and_delete_elem at libbpf.c:11031:5 in libbpf.h
// bpf_map__delete_elem at libbpf.c:11019:5 in libbpf.h
// bpf_map__lookup_elem at libbpf.c:10993:5 in libbpf.h
// bpf_map__update_elem at libbpf.c:11006:5 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

static void dummy_file_setup(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd >= 0) {
        write(fd, Data, Size);
        close(fd);
    }
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    struct bpf_map *map = NULL;
    void *key = NULL, *next_key = NULL, *value = NULL;
    size_t key_sz = 0, value_sz = 0;
    __u64 flags = 0;
    int result;

    if (Size < sizeof(size_t) * 2 + sizeof(__u64)) {
        return 0;
    }

    key_sz = *(size_t *)Data;
    value_sz = *(size_t *)(Data + sizeof(size_t));
    flags = *(__u64 *)(Data + sizeof(size_t) * 2);

    if (Size < sizeof(size_t) * 2 + sizeof(__u64) + key_sz + value_sz) {
        return 0;
    }

    key = (void *)(Data + sizeof(size_t) * 2 + sizeof(__u64));
    next_key = malloc(key_sz);
    value = (void *)(Data + sizeof(size_t) * 2 + sizeof(__u64) + key_sz);

    if (!next_key) {
        return 0;
    }

    dummy_file_setup(Data, Size);

    // Ensure map is initialized or handle this safely
    if (map) {
        // Fuzz bpf_map__get_next_key
        result = bpf_map__get_next_key(map, key, next_key, key_sz);
        if (result != 0 && result != -ENOENT) {
            // Handle error
        }

        // Fuzz bpf_map__set_key_size
        result = bpf_map__set_key_size(map, key_sz);
        if (result != 0) {
            // Handle error
        }

        // Fuzz bpf_map__lookup_and_delete_elem
        result = bpf_map__lookup_and_delete_elem(map, key, key_sz, value, value_sz, flags);
        if (result != 0) {
            // Handle error
        }

        // Fuzz bpf_map__delete_elem
        result = bpf_map__delete_elem(map, key, key_sz, flags);
        if (result != 0) {
            // Handle error
        }

        // Fuzz bpf_map__lookup_elem
        result = bpf_map__lookup_elem(map, key, key_sz, value, value_sz, flags);
        if (result != 0) {
            // Handle error
        }

        // Fuzz bpf_map__update_elem
        result = bpf_map__update_elem(map, key, key_sz, value, value_sz, flags);
        if (result != 0) {
            // Handle error
        }
    }

    free(next_key);
    return 0;
}