// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__open_file at libbpf.c:8399:1 in libbpf.h
// bpf_object__load at libbpf.c:8994:5 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
// bpf_object__find_map_by_name at libbpf.c:10901:1 in libbpf.h
// bpf_map__pin_path at libbpf.c:9213:13 in libbpf.h
// bpf_map__set_pin_path at libbpf.c:9195:5 in libbpf.h
// bpf_map__pin at libbpf.c:9095:5 in libbpf.h
// bpf_map__unpin at libbpf.c:9159:5 in libbpf.h
// bpf_map__name at libbpf.c:10562:13 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>

static struct bpf_object *load_bpf_object(const char *path) {
    struct bpf_object *obj = NULL;
    obj = bpf_object__open_file(path, NULL);
    if (!obj) {
        return NULL;
    }
    int err = bpf_object__load(obj);
    if (err) {
        bpf_object__close(obj);
        return NULL;
    }
    return obj;
}

static void cleanup_bpf_object(struct bpf_object *obj) {
    if (obj) {
        bpf_object__close(obj);
    }
}

int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Step 1: Prepare environment
    struct bpf_object *obj = load_bpf_object("./dummy_file");
    if (!obj) {
        return 0;
    }

    // Step 2: Find map by name
    char map_name[Size + 1];
    memcpy(map_name, Data, Size);
    map_name[Size] = '\0';
    struct bpf_map *map = bpf_object__find_map_by_name(obj, map_name);

    // Step 3: Explore different states
    if (map) {
        const char *pin_path = bpf_map__pin_path(map);

        // Set pin path using fuzzer data
        bpf_map__set_pin_path(map, map_name);

        // Pin the map
        bpf_map__pin(map, pin_path);

        // Unpin the map
        bpf_map__unpin(map, pin_path);

        // Get map name
        const char *name = bpf_map__name(map);
        if (name) {
            printf("Map name: %s\n", name);
        }
    }

    // Step 4: Cleanup
    cleanup_bpf_object(obj);

    return 0;
}