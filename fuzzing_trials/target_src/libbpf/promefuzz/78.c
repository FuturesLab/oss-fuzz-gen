// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// libbpf_prog_type_by_name at libbpf.c:10112:5 in libbpf.h
// libbpf_bpf_attach_type_str at libbpf.c:10138:13 in libbpf.h
// libbpf_strerror at libbpf_utils.c:47:5 in libbpf.h
// libbpf_find_vmlinux_btf_id at libbpf.c:10355:5 in libbpf.h
// libbpf_attach_type_by_name at libbpf.c:10508:5 in libbpf.h
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

static void fuzz_libbpf_prog_type_by_name(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    char name[256];
    strncpy(name, (const char *)Data, Size < 255 ? Size : 255);
    name[Size < 255 ? Size : 255] = '\0';

    enum bpf_prog_type prog_type;
    enum bpf_attach_type expected_attach_type;
    libbpf_prog_type_by_name(name, &prog_type, &expected_attach_type);
}

static void fuzz_libbpf_bpf_attach_type_str(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_attach_type)) return;

    enum bpf_attach_type attach_type;
    memcpy(&attach_type, Data, sizeof(enum bpf_attach_type));

    libbpf_bpf_attach_type_str(attach_type);
}

static void fuzz_libbpf_strerror(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + 1) return;

    int err_code;
    memcpy(&err_code, Data, sizeof(int));

    char buf[256];
    size_t buf_size = Size - sizeof(int) > 255 ? 255 : Size - sizeof(int);

    libbpf_strerror(err_code, buf, buf_size);
}

static void fuzz_libbpf_find_vmlinux_btf_id(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_attach_type) + 1) return;

    enum bpf_attach_type attach_type;
    memcpy(&attach_type, Data, sizeof(enum bpf_attach_type));

    char name[256];
    strncpy(name, (const char *)(Data + sizeof(enum bpf_attach_type)), Size - sizeof(enum bpf_attach_type) < 255 ? Size - sizeof(enum bpf_attach_type) : 255);
    name[Size - sizeof(enum bpf_attach_type) < 255 ? Size - sizeof(enum bpf_attach_type) : 255] = '\0';

    libbpf_find_vmlinux_btf_id(name, attach_type);
}

static void fuzz_libbpf_attach_type_by_name(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    char name[256];
    strncpy(name, (const char *)Data, Size < 255 ? Size : 255);
    name[Size < 255 ? Size : 255] = '\0';

    enum bpf_attach_type attach_type;
    libbpf_attach_type_by_name(name, &attach_type);
}

static void fuzz_libbpf_register_prog_handler(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(enum bpf_prog_type) + sizeof(enum bpf_attach_type) + sizeof(struct libbpf_prog_handler_opts)) return;

    char sec[256];
    strncpy(sec, (const char *)Data, Size < 255 ? Size : 255);
    sec[Size < 255 ? Size : 255] = '\0';

    enum bpf_prog_type prog_type;
    memcpy(&prog_type, Data + 256, sizeof(enum bpf_prog_type));

    enum bpf_attach_type attach_type;
    memcpy(&attach_type, Data + 256 + sizeof(enum bpf_prog_type), sizeof(enum bpf_attach_type));

    struct libbpf_prog_handler_opts opts;
    memcpy(&opts, Data + 256 + sizeof(enum bpf_prog_type) + sizeof(enum bpf_attach_type), sizeof(struct libbpf_prog_handler_opts));

    libbpf_register_prog_handler(sec, prog_type, attach_type, &opts);
}

int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size) {
    fuzz_libbpf_prog_type_by_name(Data, Size);
    fuzz_libbpf_bpf_attach_type_str(Data, Size);
    fuzz_libbpf_strerror(Data, Size);
    fuzz_libbpf_find_vmlinux_btf_id(Data, Size);
    fuzz_libbpf_attach_type_by_name(Data, Size);
    fuzz_libbpf_register_prog_handler(Data, Size);

    return 0;
}