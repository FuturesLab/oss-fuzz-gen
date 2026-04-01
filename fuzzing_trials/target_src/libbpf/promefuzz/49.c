// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__find_map_by_name at libbpf.c:10901:1 in libbpf.h
// bpf_object__find_program_by_name at libbpf.c:4475:1 in libbpf.h
// bpf_object__open at libbpf.c:8407:20 in libbpf.h
// bpf_map__exclusive_program at libbpf.c:10850:21 in libbpf.h
// bpf_map__autoattach at libbpf.c:4974:6 in libbpf.h
// bpf_map__set_exclusive_program at libbpf.c:10834:5 in libbpf.h
// bpf_map__set_autocreate at libbpf.c:4956:5 in libbpf.h
// bpf_program__set_expected_attach_type at libbpf.c:9723:5 in libbpf.h
// bpf_map__set_autoattach at libbpf.c:4965:5 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <libbpf.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static struct bpf_map *create_dummy_map(struct bpf_object *obj) {
    // Creating a dummy BPF map
    struct bpf_map *map = bpf_object__find_map_by_name(obj, "dummy_map");
    if (!map) {
        fprintf(stderr, "Failed to find the BPF map\n");
        return NULL;
    }
    return map;
}

static struct bpf_program *create_dummy_program(struct bpf_object *obj) {
    // Creating a dummy BPF program
    struct bpf_program *prog = bpf_object__find_program_by_name(obj, "dummy_prog");
    if (!prog) {
        fprintf(stderr, "Failed to find the BPF program\n");
        return NULL;
    }
    return prog;
}

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Assuming dummy_file contains a valid BPF object with a map and a program
    struct bpf_object *obj = bpf_object__open("./dummy_file");
    if (!obj) return 0;

    struct bpf_map *map = create_dummy_map(obj);
    struct bpf_program *prog = create_dummy_program(obj);
    if (!map || !prog) goto cleanup;

    // Fuzz bpf_map__exclusive_program
    struct bpf_program *exclusive_prog = bpf_map__exclusive_program(map);
    if (exclusive_prog) {
        // Do something with exclusive_prog if needed
    }

    // Fuzz bpf_map__autoattach
    bool autoattach = bpf_map__autoattach(map);

    // Fuzz bpf_map__set_exclusive_program
    int res_exclusive = bpf_map__set_exclusive_program(map, prog);

    // Fuzz bpf_map__set_autocreate
    bool autocreate = Data[0] % 2;
    int res_autocreate = bpf_map__set_autocreate(map, autocreate);

    // Fuzz bpf_program__set_expected_attach_type
    enum bpf_attach_type attach_type = Data[0] % __MAX_BPF_ATTACH_TYPE;
    int res_attach_type = bpf_program__set_expected_attach_type(prog, attach_type);

    // Fuzz bpf_map__set_autoattach
    bool set_autoattach = Data[0] % 2;
    int res_set_autoattach = bpf_map__set_autoattach(map, set_autoattach);

cleanup:
    if (obj) bpf_object__close(obj);

    return 0;
}