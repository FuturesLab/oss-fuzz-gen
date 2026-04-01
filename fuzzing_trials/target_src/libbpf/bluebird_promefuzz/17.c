#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "libbpf.h"
#include "/src/libbpf/include/uapi/linux/fcntl.h"
#include <unistd.h>

static void fuzz_libbpf_bpf_map_type_str(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_map_type))
        return;

    enum bpf_map_type map_type;
    memcpy(&map_type, Data, sizeof(map_type));
    const char *result = libbpf_bpf_map_type_str(map_type);
}

static void fuzz_libbpf_bpf_prog_type_str(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_prog_type))
        return;

    enum bpf_prog_type prog_type;
    memcpy(&prog_type, Data, sizeof(prog_type));
    const char *result = libbpf_bpf_prog_type_str(prog_type);
}

static void fuzz_libbpf_prog_type_by_name(const uint8_t *Data, size_t Size) {
    if (Size == 0)
        return;

    char name[256];
    size_t name_len = Size < sizeof(name) - 1 ? Size : sizeof(name) - 1;
    memcpy(name, Data, name_len);
    name[name_len] = '\0';

    enum bpf_prog_type prog_type;
    enum bpf_attach_type expected_attach_type;
    int result = libbpf_prog_type_by_name(name, &prog_type, &expected_attach_type);
}

static void fuzz_libbpf_bpf_attach_type_str(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_attach_type))
        return;

    enum bpf_attach_type attach_type;
    memcpy(&attach_type, Data, sizeof(attach_type));
    const char *result = libbpf_bpf_attach_type_str(attach_type);
}

static void fuzz_libbpf_bpf_link_type_str(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_link_type))
        return;

    enum bpf_link_type link_type;
    memcpy(&link_type, Data, sizeof(link_type));
    const char *result = libbpf_bpf_link_type_str(link_type);
}

static void fuzz_libbpf_probe_bpf_prog_type(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_prog_type))
        return;

    enum bpf_prog_type prog_type;
    memcpy(&prog_type, Data, sizeof(prog_type));
    int result = libbpf_probe_bpf_prog_type(prog_type, NULL);
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    fuzz_libbpf_bpf_map_type_str(Data, Size);
    fuzz_libbpf_bpf_prog_type_str(Data, Size);
    fuzz_libbpf_prog_type_by_name(Data, Size);
    fuzz_libbpf_bpf_attach_type_str(Data, Size);
    fuzz_libbpf_bpf_link_type_str(Data, Size);
    fuzz_libbpf_probe_bpf_prog_type(Data, Size);

    return 0;
}