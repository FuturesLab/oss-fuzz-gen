// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// libbpf_prog_type_by_name at libbpf.c:10112:5 in libbpf.h
// libbpf_probe_bpf_prog_type at libbpf_probes.c:205:5 in libbpf.h
// libbpf_probe_bpf_map_type at libbpf_probes.c:409:5 in libbpf.h
// libbpf_probe_bpf_helper at libbpf_probes.c:420:5 in libbpf.h
// libbpf_find_vmlinux_btf_id at libbpf.c:10355:5 in libbpf.h
// libbpf_register_prog_handler at libbpf.c:9935:5 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <libbpf.h>
#include <libbpf.h>

static int fuzz_libbpf_prog_type_by_name(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    char *name = strndup((const char *)Data, Size);
    if (!name) return 0;

    enum bpf_prog_type prog_type;
    enum bpf_attach_type expected_attach_type;
    libbpf_prog_type_by_name(name, &prog_type, &expected_attach_type);

    free(name);
    return 0;
}

static int fuzz_libbpf_probe_bpf_prog_type(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_prog_type)) return 0;

    enum bpf_prog_type prog_type;
    memcpy(&prog_type, Data, sizeof(enum bpf_prog_type));

    libbpf_probe_bpf_prog_type(prog_type, NULL);
    return 0;
}

static int fuzz_libbpf_probe_bpf_map_type(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_map_type)) return 0;

    enum bpf_map_type map_type;
    memcpy(&map_type, Data, sizeof(enum bpf_map_type));

    libbpf_probe_bpf_map_type(map_type, NULL);
    return 0;
}

static int fuzz_libbpf_probe_bpf_helper(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_prog_type) + sizeof(enum bpf_func_id)) return 0;

    enum bpf_prog_type prog_type;
    enum bpf_func_id helper_id;
    memcpy(&prog_type, Data, sizeof(enum bpf_prog_type));
    memcpy(&helper_id, Data + sizeof(enum bpf_prog_type), sizeof(enum bpf_func_id));

    libbpf_probe_bpf_helper(prog_type, helper_id, NULL);
    return 0;
}

static int fuzz_libbpf_find_vmlinux_btf_id(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_attach_type)) return 0;

    char *name = strndup((const char *)Data, Size - sizeof(enum bpf_attach_type));
    if (!name) return 0;

    enum bpf_attach_type attach_type;
    memcpy(&attach_type, Data + Size - sizeof(enum bpf_attach_type), sizeof(enum bpf_attach_type));

    libbpf_find_vmlinux_btf_id(name, attach_type);

    free(name);
    return 0;
}

static int fuzz_libbpf_register_prog_handler(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_prog_type) + sizeof(enum bpf_attach_type)) return 0;

    char *sec = strndup((const char *)Data, Size - sizeof(enum bpf_prog_type) - sizeof(enum bpf_attach_type));
    if (!sec) return 0;

    enum bpf_prog_type prog_type;
    enum bpf_attach_type exp_attach_type;
    memcpy(&prog_type, Data + Size - sizeof(enum bpf_prog_type) - sizeof(enum bpf_attach_type), sizeof(enum bpf_prog_type));
    memcpy(&exp_attach_type, Data + Size - sizeof(enum bpf_attach_type), sizeof(enum bpf_attach_type));

    libbpf_register_prog_handler(sec, prog_type, exp_attach_type, NULL);

    free(sec);
    return 0;
}

int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size) {
    fuzz_libbpf_prog_type_by_name(Data, Size);
    fuzz_libbpf_probe_bpf_prog_type(Data, Size);
    fuzz_libbpf_probe_bpf_map_type(Data, Size);
    fuzz_libbpf_probe_bpf_helper(Data, Size);
    fuzz_libbpf_find_vmlinux_btf_id(Data, Size);
    fuzz_libbpf_register_prog_handler(Data, Size);
    return 0;
}