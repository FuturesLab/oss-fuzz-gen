// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__next_program at libbpf.c:9575:1 in libbpf.h
// bpf_program__line_info_cnt at libbpf.c:9800:7 in libbpf.h
// bpf_program__log_level at libbpf.c:9747:7 in libbpf.h
// bpf_program__section_name at libbpf.c:9608:13 in libbpf.h
// bpf_program__set_ifindex at libbpf.c:9598:6 in libbpf.h
// bpf_program__attach_netns at libbpf.c:13207:1 in libbpf.h
// bpf_link__destroy at libbpf.c:11103:5 in libbpf.h
// bpf_object__find_program_by_name at libbpf.c:4475:1 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
// bpf_object__open at libbpf.c:8407:20 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    // Open a dummy BPF object
    struct bpf_object *obj = bpf_object__open("./dummy_file");
    if (!obj) return 0;

    // Iterate over BPF programs within the object
    struct bpf_program *prog;
    bpf_object__for_each_program(prog, obj) {
        // Fuzz bpf_program__line_info_cnt
        __u32 line_info_cnt = bpf_program__line_info_cnt(prog);
        (void)line_info_cnt;

        // Fuzz bpf_program__log_level
        __u32 log_level = bpf_program__log_level(prog);
        (void)log_level;

        // Fuzz bpf_program__section_name
        const char *section_name = bpf_program__section_name(prog);
        if (section_name) {
            (void)section_name;
        }

        // Fuzz bpf_program__set_ifindex
        if (Size > 0) {
            __u32 ifindex = Data[0]; // Use the first byte of Data as ifindex
            bpf_program__set_ifindex(prog, ifindex);
        }

        // Fuzz bpf_program__attach_netns
        if (Size > 0) {
            int netns_fd = (int)(Data[0] % 256); // Use the first byte of Data as netns_fd
            struct bpf_link *link = bpf_program__attach_netns(prog, netns_fd);
            if (link) {
                // Simulate detaching and deallocating the link
                bpf_link__destroy(link);
            }
        }
    }

    // Fuzz bpf_object__find_program_by_name
    if (Size > 0) {
        char name[16];
        snprintf(name, sizeof(name), "prog_%u", Data[0]);
        struct bpf_program *found_prog = bpf_object__find_program_by_name(obj, name);
        if (found_prog) {
            (void)found_prog;
        }
    }

    bpf_object__close(obj);
    return 0;
}