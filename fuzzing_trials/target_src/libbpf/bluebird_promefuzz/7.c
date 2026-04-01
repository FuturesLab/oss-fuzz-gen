#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "/src/libbpf/include/uapi/linux/fcntl.h"
#include <unistd.h>
#include "libbpf.h"

static struct bpf_linker_opts *create_linker_opts() {
    struct bpf_linker_opts *opts = malloc(sizeof(struct bpf_linker_opts));
    if (opts) {
        opts->sz = sizeof(struct bpf_linker_opts);
    }
    return opts;
}

static struct bpf_linker_file_opts *create_linker_file_opts() {
    struct bpf_linker_file_opts *opts = malloc(sizeof(struct bpf_linker_file_opts));
    if (opts) {
        opts->sz = sizeof(struct bpf_linker_file_opts);
    }
    return opts;
}

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file if needed
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    struct bpf_linker_opts *linker_opts = create_linker_opts();
    struct bpf_linker_file_opts *file_opts = create_linker_file_opts();

    // Test bpf_linker__new
    struct bpf_linker *linker = bpf_linker__new("./dummy_file", linker_opts);
    if (linker) {
        // Test bpf_linker__add_fd
        int fd = open("./dummy_file", O_RDONLY);
        if (fd != -1) {
            bpf_linker__add_fd(linker, fd, file_opts);
            close(fd);
        }

        // Test bpf_linker__add_file
        bpf_linker__add_file(linker, "./dummy_file", file_opts);

        // Test bpf_linker__finalize
        bpf_linker__finalize(linker);

        // Clean up
        bpf_linker__free(linker);
    }

    // Test bpf_linker__new_fd
    int fd = open("./dummy_file", O_RDONLY);
    if (fd != -1) {
        struct bpf_linker *linker_fd = bpf_linker__new_fd(fd, linker_opts);
        if (linker_fd) {
            bpf_linker__free(linker_fd);
        }
        close(fd);
    }

    // Clean up
    free(linker_opts);
    free(file_opts);
    remove("./dummy_file");

    return 0;
}