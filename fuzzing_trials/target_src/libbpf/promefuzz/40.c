// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
// bpf_program__attach_perf_event at libbpf.c:11338:18 in libbpf.h
// bpf_program__attach_sockmap at libbpf.c:13213:1 in libbpf.h
// bpf_program__attach_netfilter at libbpf.c:13403:18 in libbpf.h
// bpf_program__attach_lsm at libbpf.c:13149:18 in libbpf.h
// bpf_program__attach_xdp at libbpf.c:13218:18 in libbpf.h
// bpf_program__attach_netkit at libbpf.c:13288:1 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <libbpf.h>

static struct bpf_program *dummy_bpf_program() {
    // Return a dummy pointer, as we cannot instantiate an incomplete type
    return (struct bpf_program *)0x1;
}

static void cleanup_bpf_link(struct bpf_link *link) {
    if (link) {
        bpf_link__destroy(link);
    }
}

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 3) {
        return 0;
    }

    int fd = open("./dummy_file", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        return 0;
    }

    struct bpf_program *prog = dummy_bpf_program();
    struct bpf_link *link = NULL;

    // Extract integers from the data
    int pfd = *((int *)(Data));
    int map_fd = *((int *)(Data + sizeof(int)));
    int ifindex = *((int *)(Data + 2 * sizeof(int)));

    // Fuzz bpf_program__attach_perf_event
    link = bpf_program__attach_perf_event(prog, pfd);
    cleanup_bpf_link(link);

    // Fuzz bpf_program__attach_sockmap
    link = bpf_program__attach_sockmap(prog, map_fd);
    cleanup_bpf_link(link);

    // Fuzz bpf_program__attach_netfilter
    struct bpf_netfilter_opts opts = { .sz = sizeof(opts) };
    link = bpf_program__attach_netfilter(prog, &opts);
    cleanup_bpf_link(link);

    // Fuzz bpf_program__attach_lsm
    link = bpf_program__attach_lsm(prog);
    cleanup_bpf_link(link);

    // Fuzz bpf_program__attach_xdp
    link = bpf_program__attach_xdp(prog, ifindex);
    cleanup_bpf_link(link);

    // Fuzz bpf_program__attach_netkit
    struct bpf_netkit_opts netkit_opts = { .sz = sizeof(netkit_opts) };
    link = bpf_program__attach_netkit(prog, ifindex, &netkit_opts);
    cleanup_bpf_link(link);

    close(fd);
    return 0;
}