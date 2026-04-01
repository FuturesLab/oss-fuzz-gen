// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_program__attach_kprobe_opts at libbpf.c:11655:1 in libbpf.h
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
// bpf_program__attach_raw_tracepoint_opts at libbpf.c:13019:1 in libbpf.h
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
// bpf_program__attach_raw_tracepoint at libbpf.c:13055:18 in libbpf.h
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
// bpf_program__attach_tracepoint_opts at libbpf.c:12946:18 in libbpf.h
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
// bpf_program__attach_kprobe_multi_opts at libbpf.c:12000:1 in libbpf.h
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
// bpf_program__attach_tracepoint at libbpf.c:12979:18 in libbpf.h
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>

static struct bpf_program *create_dummy_bpf_program() {
    // This function should create and return a dummy bpf_program object
    // For simplicity, we're returning NULL in this example
    return NULL;
}

static void fuzz_bpf_program__attach_raw_tracepoint(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    char tp_name[256] = {0};

    if (!prog) {
        return; // Prevent further execution if prog is NULL
    }

    if (Size > 0) {
        size_t len = Size < sizeof(tp_name) ? Size : sizeof(tp_name) - 1;
        memcpy(tp_name, Data, len);
    }

    struct bpf_link *link = bpf_program__attach_raw_tracepoint(prog, tp_name);
    if (link) {
        bpf_link__destroy(link);
    }
}

static void fuzz_bpf_program__attach_tracepoint_opts(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    char tp_category[256] = {0};
    char tp_name[256] = {0};
    struct bpf_tracepoint_opts opts = {0};

    if (!prog) {
        return; // Prevent further execution if prog is NULL
    }

    if (Size > 0) {
        size_t len = Size / 2 < sizeof(tp_category) ? Size / 2 : sizeof(tp_category) - 1;
        memcpy(tp_category, Data, len);
        len = Size / 2 < sizeof(tp_name) ? Size / 2 : sizeof(tp_name) - 1;
        memcpy(tp_name, Data + Size / 2, len);
    }

    struct bpf_link *link = bpf_program__attach_tracepoint_opts(prog, tp_category, tp_name, &opts);
    if (link) {
        bpf_link__destroy(link);
    }
}

static void fuzz_bpf_program__attach_kprobe_multi_opts(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    char pattern[256] = {0};
    struct bpf_kprobe_multi_opts opts = {0};

    if (!prog) {
        return; // Prevent further execution if prog is NULL
    }

    if (Size > 0) {
        size_t len = Size < sizeof(pattern) ? Size : sizeof(pattern) - 1;
        memcpy(pattern, Data, len);
    }

    struct bpf_link *link = bpf_program__attach_kprobe_multi_opts(prog, pattern, &opts);
    if (link) {
        bpf_link__destroy(link);
    }
}

static void fuzz_bpf_program__attach_tracepoint(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    char tp_category[256] = {0};
    char tp_name[256] = {0};

    if (!prog) {
        return; // Prevent further execution if prog is NULL
    }

    if (Size > 0) {
        size_t len = Size / 2 < sizeof(tp_category) ? Size / 2 : sizeof(tp_category) - 1;
        memcpy(tp_category, Data, len);
        len = Size / 2 < sizeof(tp_name) ? Size / 2 : sizeof(tp_name) - 1;
        memcpy(tp_name, Data + Size / 2, len);
    }

    struct bpf_link *link = bpf_program__attach_tracepoint(prog, tp_category, tp_name);
    if (link) {
        bpf_link__destroy(link);
    }
}

static void fuzz_bpf_program__attach_kprobe_opts(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    char func_name[256] = {0};
    struct bpf_kprobe_opts opts = {0};

    if (!prog) {
        return; // Prevent further execution if prog is NULL
    }

    if (Size > 0) {
        size_t len = Size < sizeof(func_name) ? Size : sizeof(func_name) - 1;
        memcpy(func_name, Data, len);
    }

    struct bpf_link *link = bpf_program__attach_kprobe_opts(prog, func_name, &opts);
    if (link) {
        bpf_link__destroy(link);
    }
}

static void fuzz_bpf_program__attach_raw_tracepoint_opts(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    char tp_name[256] = {0};
    struct bpf_raw_tracepoint_opts opts = {0};

    if (!prog) {
        return; // Prevent further execution if prog is NULL
    }

    if (Size > 0) {
        size_t len = Size < sizeof(tp_name) ? Size : sizeof(tp_name) - 1;
        memcpy(tp_name, Data, len);
    }

    struct bpf_link *link = bpf_program__attach_raw_tracepoint_opts(prog, tp_name, &opts);
    if (link) {
        bpf_link__destroy(link);
    }
}

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    fuzz_bpf_program__attach_raw_tracepoint(Data, Size);
    fuzz_bpf_program__attach_tracepoint_opts(Data, Size);
    fuzz_bpf_program__attach_kprobe_multi_opts(Data, Size);
    fuzz_bpf_program__attach_tracepoint(Data, Size);
    fuzz_bpf_program__attach_kprobe_opts(Data, Size);
    fuzz_bpf_program__attach_raw_tracepoint_opts(Data, Size);
    return 0;
}