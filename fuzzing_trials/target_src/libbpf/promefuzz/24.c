// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__open at libbpf.c:8407:20 in libbpf.h
// bpf_object__btf_fd at libbpf.c:9516:5 in libbpf.h
// bpf_object__name at libbpf.c:9496:13 in libbpf.h
// bpf_object__token_fd at libbpf.c:9506:5 in libbpf.h
// bpf_object__find_map_fd_by_name at libbpf.c:10928:1 in libbpf.h
// bpf_object__find_program_by_name at libbpf.c:4475:1 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <libbpf.h>

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare a dummy file with the input data
    prepare_dummy_file(Data, Size);

    // Attempt to open the BPF object
    struct bpf_object *obj = bpf_object__open("./dummy_file");
    if (!obj) {
        // Failed to open, cleanup and return
        return 0;
    }

    // Test bpf_object__btf_fd
    int btf_fd = bpf_object__btf_fd(obj);
    if (btf_fd < 0) {
        // Handle error case if needed
    }

    // Test bpf_object__name
    const char *name = bpf_object__name(obj);
    if (name) {
        // Use the name if needed
    }

    // Test bpf_object__token_fd
    int token_fd = bpf_object__token_fd(obj);
    if (token_fd < 0) {
        // Handle error case if needed
    }

    // Test bpf_object__find_map_fd_by_name
    int map_fd = bpf_object__find_map_fd_by_name(obj, "dummy_map_name");
    if (map_fd < 0) {
        // Handle error case if needed
    }

    // Test bpf_object__find_program_by_name
    struct bpf_program *prog = bpf_object__find_program_by_name(obj, "dummy_program_name");
    if (!prog) {
        // Handle error case if needed
    }

    // Cleanup
    bpf_object__close(obj);

    return 0;
}