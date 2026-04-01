// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__open at libbpf.c:8407:20 in libbpf.h
// bpf_object__next_program at libbpf.c:9575:1 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
// bpf_program__set_autoload at libbpf.c:9618:5 in libbpf.h
// bpf_program__autoload at libbpf.c:9613:6 in libbpf.h
// bpf_program__set_expected_attach_type at libbpf.c:9723:5 in libbpf.h
// bpf_program__set_flags at libbpf.c:9738:5 in libbpf.h
// bpf_program__attach at libbpf.c:13443:18 in libbpf.h
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
// bpf_program__autoattach at libbpf.c:9627:6 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>
#include <errno.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(bool) + sizeof(enum bpf_attach_type) + sizeof(__u32)) {
        return 0; // Not enough data for meaningful fuzzing
    }

    struct bpf_object *obj = bpf_object__open("./dummy_file");
    if (!obj) {
        return 0;
    }

    struct bpf_program *prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        return 0;
    }

    // Fuzz bpf_program__set_autoload
    bool autoload = Data[0] % 2; // Use first byte for boolean
    bpf_program__set_autoload(prog, autoload);

    // Fuzz bpf_program__autoload
    bpf_program__autoload(prog);

    // Fuzz bpf_program__set_expected_attach_type
    enum bpf_attach_type attach_type = (enum bpf_attach_type)Data[1];
    bpf_program__set_expected_attach_type(prog, attach_type);

    // Fuzz bpf_program__set_flags
    __u32 flags = *((__u32 *)(Data + 2));
    bpf_program__set_flags(prog, flags);

    // Fuzz bpf_program__attach
    struct bpf_link *link = bpf_program__attach(prog);
    if (link) {
        bpf_link__destroy(link);
    }

    // Fuzz bpf_program__autoattach
    bpf_program__autoattach(prog);

    bpf_object__close(obj);

    return 0;
}