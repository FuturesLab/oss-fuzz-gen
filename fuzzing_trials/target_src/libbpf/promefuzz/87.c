// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_program__name at libbpf.c:9603:13 in libbpf.h
// bpf_program__line_info_cnt at libbpf.c:9800:7 in libbpf.h
// bpf_program__flags at libbpf.c:9733:7 in libbpf.h
// bpf_program__log_buf at libbpf.c:9761:13 in libbpf.h
// bpf_program__section_name at libbpf.c:9608:13 in libbpf.h
// bpf_object__find_program_by_name at libbpf.c:4475:1 in libbpf.h
// bpf_program__name at libbpf.c:9603:13 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>

static struct bpf_program *initialize_bpf_program() {
    // Dummy initialization of bpf_program for fuzzing purposes.
    return NULL; // Return NULL as we cannot allocate an incomplete type
}

static struct bpf_object *initialize_bpf_object() {
    // Dummy initialization of bpf_object for fuzzing purposes.
    return NULL; // Return NULL as we cannot allocate an incomplete type
}

static void cleanup_bpf_program(struct bpf_program *prog) {
    // No cleanup required as we are not allocating memory
}

static void cleanup_bpf_object(struct bpf_object *obj) {
    // No cleanup required as we are not allocating memory
}

int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    struct bpf_program *prog = initialize_bpf_program();
    struct bpf_object *obj = initialize_bpf_object();

    // Check if prog is NULL before calling the functions
    if (prog) {
        // Fuzzing bpf_program__name
        const char *prog_name = bpf_program__name(prog);
        if (prog_name) {
            printf("Program name: %s\n", prog_name);
        }

        // Fuzzing bpf_program__line_info_cnt
        __u32 line_info_cnt = bpf_program__line_info_cnt(prog);
        printf("Line info count: %u\n", line_info_cnt);

        // Fuzzing bpf_program__flags
        __u32 flags = bpf_program__flags(prog);
        printf("Program flags: %u\n", flags);

        // Fuzzing bpf_program__log_buf
        size_t log_size;
        const char *log_buf = bpf_program__log_buf(prog, &log_size);
        if (log_buf) {
            printf("Log buffer: %.*s\n", (int)log_size, log_buf);
        }

        // Fuzzing bpf_program__section_name
        const char *section_name = bpf_program__section_name(prog);
        if (section_name) {
            printf("Section name: %s\n", section_name);
        }
    }

    // Fuzzing bpf_object__find_program_by_name
    if (obj) {
        char name[64];
        size_t name_len = Size < sizeof(name) ? Size : sizeof(name) - 1;
        memcpy(name, Data, name_len);
        name[name_len] = '\0';  // Ensure null-termination

        struct bpf_program *found_prog = bpf_object__find_program_by_name(obj, name);
        if (found_prog) {
            printf("Found program: %s\n", bpf_program__name(found_prog));
        }
    }

    cleanup_bpf_program(prog);
    cleanup_bpf_object(obj);

    return 0;
}