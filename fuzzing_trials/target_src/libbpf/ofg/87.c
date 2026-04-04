#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/bpf.h>
#include "/src/libbpf/src/libbpf.h" // Corrected include path for libbpf

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Create a temporary file to store the fuzz input
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Load BPF program from the temporary file
    struct bpf_object *obj;
    struct bpf_program *prog;
    int prog_fd;

    obj = bpf_object__open_file(tmpl, NULL);
    if (!obj) {
        unlink(tmpl);
        return 0;
    }

    if (bpf_object__load(obj) < 0) {
        bpf_object__close(obj);
        unlink(tmpl);
        return 0;
    }

    // Assuming there's at least one program in the BPF object
    prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        unlink(tmpl);
        return 0;
    }

    prog_fd = bpf_program__fd(prog);
    if (prog_fd < 0) {
        bpf_object__close(obj);
        unlink(tmpl);
        return 0;
    }

    // Clean up
    bpf_object__close(obj);
    unlink(tmpl);

    return 0;
}