// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_linker__new_fd at linker.c:269:20 in libbpf.h
// bpf_linker__add_fd at linker.c:541:5 in libbpf.h
// bpf_linker__add_buf at linker.c:561:5 in libbpf.h
// bpf_linker__add_file at linker.c:518:5 in libbpf.h
// bpf_linker__finalize at linker.c:2752:5 in libbpf.h
// bpf_linker__free at linker.c:190:6 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>

static void initialize_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fwrite("dummy content", 1, 13, file);
        fclose(file);
    }
}

static struct bpf_linker *create_dummy_linker() {
    int fd = open("./dummy_file", O_RDONLY);
    if (fd < 0) return NULL;

    struct bpf_linker_opts opts = { .sz = sizeof(struct bpf_linker_opts) };
    struct bpf_linker *linker = bpf_linker__new_fd(fd, &opts);
    close(fd);
    return linker;
}

int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    initialize_dummy_file();

    struct bpf_linker *linker = create_dummy_linker();
    if (!linker) return 0;

    struct bpf_linker_file_opts file_opts = { .sz = sizeof(struct bpf_linker_file_opts) };
    int fd = open("./dummy_file", O_RDONLY);
    if (fd >= 0) {
        bpf_linker__add_fd(linker, fd, &file_opts);
        close(fd);
    }

    bpf_linker__add_buf(linker, (void *)Data, Size, &file_opts);

    bpf_linker__add_file(linker, "./dummy_file", &file_opts);

    bpf_linker__finalize(linker);

    bpf_linker__free(linker);

    return 0;
}