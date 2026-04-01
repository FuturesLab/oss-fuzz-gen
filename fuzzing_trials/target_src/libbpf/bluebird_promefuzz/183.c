#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "libbpf.h"

static void fuzz_libbpf_prog_type_by_name(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return;
    }

    char name[Size + 1];
    memcpy(name, Data, Size);
    name[Size] = '\0';

    enum bpf_prog_type prog_type;
    enum bpf_attach_type expected_attach_type;
    libbpf_prog_type_by_name(name, &prog_type, &expected_attach_type);
}

static void fuzz_libbpf_bpf_attach_type_str(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_attach_type)) {
        return;
    }

    enum bpf_attach_type attach_type;
    memcpy(&attach_type, Data, sizeof(enum bpf_attach_type));

    libbpf_bpf_attach_type_str(attach_type);
}

static void fuzz_libbpf_probe_bpf_prog_type(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_prog_type)) {
        return;
    }

    enum bpf_prog_type prog_type;
    memcpy(&prog_type, Data, sizeof(enum bpf_prog_type));

    libbpf_probe_bpf_prog_type(prog_type, NULL);
}

static void fuzz_libbpf_probe_bpf_helper(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_prog_type) + sizeof(enum bpf_func_id)) {
        return;
    }

    enum bpf_prog_type prog_type;
    enum bpf_func_id helper_id;
    memcpy(&prog_type, Data, sizeof(enum bpf_prog_type));
    memcpy(&helper_id, Data + sizeof(enum bpf_prog_type), sizeof(enum bpf_func_id));


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of libbpf_probe_bpf_helper
    libbpf_probe_bpf_helper(prog_type, helper_id, (const void *)"r");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


}

static void fuzz_libbpf_find_vmlinux_btf_id(const uint8_t *Data, size_t Size) {
    if (Size < 1 + sizeof(enum bpf_attach_type)) {
        return;
    }

    char name[Size - sizeof(enum bpf_attach_type) + 1];
    memcpy(name, Data, Size - sizeof(enum bpf_attach_type));
    name[Size - sizeof(enum bpf_attach_type)] = '\0';

    enum bpf_attach_type attach_type;
    memcpy(&attach_type, Data + Size - sizeof(enum bpf_attach_type), sizeof(enum bpf_attach_type));

    libbpf_find_vmlinux_btf_id(name, attach_type);
}

static void fuzz_libbpf_register_prog_handler(const uint8_t *Data, size_t Size) {
    if (Size < 1 + sizeof(enum bpf_prog_type) + sizeof(enum bpf_attach_type)) {
        return;
    }

    char sec[Size - sizeof(enum bpf_prog_type) - sizeof(enum bpf_attach_type) + 1];
    memcpy(sec, Data, Size - sizeof(enum bpf_prog_type) - sizeof(enum bpf_attach_type));
    sec[Size - sizeof(enum bpf_prog_type) - sizeof(enum bpf_attach_type)] = '\0';

    enum bpf_prog_type prog_type;
    enum bpf_attach_type exp_attach_type;
    memcpy(&prog_type, Data + Size - sizeof(enum bpf_prog_type) - sizeof(enum bpf_attach_type), sizeof(enum bpf_prog_type));
    memcpy(&exp_attach_type, Data + Size - sizeof(enum bpf_attach_type), sizeof(enum bpf_attach_type));

    struct libbpf_prog_handler_opts opts = {0};
    libbpf_register_prog_handler(sec, prog_type, exp_attach_type, &opts);
}

int LLVMFuzzerTestOneInput_183(const uint8_t *Data, size_t Size) {
    fuzz_libbpf_prog_type_by_name(Data, Size);
    fuzz_libbpf_bpf_attach_type_str(Data, Size);
    fuzz_libbpf_probe_bpf_prog_type(Data, Size);
    fuzz_libbpf_probe_bpf_helper(Data, Size);
    fuzz_libbpf_find_vmlinux_btf_id(Data, Size);
    fuzz_libbpf_register_prog_handler(Data, Size);
    return 0;
}