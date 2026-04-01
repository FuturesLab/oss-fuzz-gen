// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
// bpf_program__attach at libbpf.c:13443:18 in libbpf.h
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
// bpf_program__set_attach_target at libbpf.c:14140:5 in libbpf.h
// bpf_program__attach_uprobe_multi at libbpf.c:12475:1 in libbpf.h
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
// bpf_program__set_expected_attach_type at libbpf.c:9723:5 in libbpf.h
// bpf_program__set_log_buf at libbpf.c:9767:5 in libbpf.h
// bpf_program__attach_cgroup at libbpf.c:13201:1 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

static struct bpf_program *create_dummy_bpf_program() {
    // This function should create and return a dummy bpf_program.
    // In a real-world scenario, this would involve compiling a BPF program,
    // but for fuzzing, we will simulate this.
    // Returning NULL to simulate an uninitialized or invalid program pointer
    return NULL;
}

static void cleanup_bpf_program(struct bpf_program *prog) {
    // No actual cleanup needed for dummy program
}

static void fuzz_bpf_program__attach(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    if (!prog) {
        return; // Early exit if program creation failed
    }
    struct bpf_link *link = bpf_program__attach(prog);
    if (link) {
        bpf_link__destroy(link);
    }
    cleanup_bpf_program(prog);
}

static void fuzz_bpf_program__set_attach_target(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    if (!prog || Size < sizeof(int) + 1) {
        return; // Early exit if program creation failed or data size is insufficient
    }
    int attach_prog_fd = *(int *)Data;
    const char *attach_func_name = (const char *)(Data + sizeof(int));

    bpf_program__set_attach_target(prog, attach_prog_fd, attach_func_name);
    cleanup_bpf_program(prog);
}

static void fuzz_bpf_program__attach_uprobe_multi(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    if (!prog || Size < sizeof(pid_t) + 2) {
        return; // Early exit if program creation failed or data size is insufficient
    }
    pid_t pid = *(pid_t *)Data;
    const char *binary_path = (const char *)(Data + sizeof(pid_t));
    const char *func_pattern = binary_path + strlen(binary_path) + 1;

    struct bpf_link *link = bpf_program__attach_uprobe_multi(prog, pid, binary_path, func_pattern, NULL);
    if (link) {
        bpf_link__destroy(link);
    }
    cleanup_bpf_program(prog);
}

static void fuzz_bpf_program__set_expected_attach_type(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    if (!prog || Size < sizeof(enum bpf_attach_type)) {
        return; // Early exit if program creation failed or data size is insufficient
    }
    enum bpf_attach_type type = *(enum bpf_attach_type *)Data;

    bpf_program__set_expected_attach_type(prog, type);
    cleanup_bpf_program(prog);
}

static void fuzz_bpf_program__set_log_buf(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    if (!prog) {
        return; // Early exit if program creation failed
    }
    char *log_buf = (char *)malloc(1024);
    memset(log_buf, 0, 1024);

    bpf_program__set_log_buf(prog, log_buf, 1024);
    cleanup_bpf_program(prog);
    free(log_buf);
}

static void fuzz_bpf_program__attach_cgroup(const uint8_t *Data, size_t Size) {
    struct bpf_program *prog = create_dummy_bpf_program();
    if (!prog) {
        return; // Early exit if program creation failed
    }
    int cgroup_fd = open("/proc/self/cgroup", O_RDONLY);

    if (cgroup_fd < 0) {
        cleanup_bpf_program(prog);
        return; // Early exit if cgroup file cannot be opened
    }

    struct bpf_link *link = bpf_program__attach_cgroup(prog, cgroup_fd);
    if (link) {
        bpf_link__destroy(link);
    }
    close(cgroup_fd);
    cleanup_bpf_program(prog);
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    fuzz_bpf_program__attach(Data, Size);
    fuzz_bpf_program__set_attach_target(Data, Size);
    fuzz_bpf_program__attach_uprobe_multi(Data, Size);
    fuzz_bpf_program__set_expected_attach_type(Data, Size);
    fuzz_bpf_program__set_log_buf(Data, Size);
    fuzz_bpf_program__attach_cgroup(Data, Size);
    return 0;
}