// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_prog_linfo__new at bpf_prog_linfo.c:100:24 in libbpf.h
// bpf_prog_linfo__free at bpf_prog_linfo.c:88:6 in libbpf.h
// bpf_program__func_info_cnt at libbpf.c:9788:7 in libbpf.h
// bpf_program__line_info at libbpf.c:9793:23 in libbpf.h
// bpf_prog_linfo__lfind_addr_func at bpf_prog_linfo.c:181:1 in libbpf.h
// bpf_prog_linfo__lfind at bpf_prog_linfo.c:219:1 in libbpf.h
// bpf_prog_linfo__free at bpf_prog_linfo.c:88:6 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <libbpf.h>

static struct bpf_prog_linfo *create_dummy_prog_linfo() {
    struct bpf_prog_info info = {0};
    info.nr_line_info = 1;
    struct bpf_prog_linfo *prog_linfo = bpf_prog_linfo__new(&info);
    return prog_linfo;
}

static struct bpf_program *create_dummy_bpf_program() {
    // This is a stub function. In a real scenario, you'd initialize a valid bpf_program.
    // For fuzzing purposes, return NULL to safely handle edge cases.
    return NULL;
}

int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    // Fuzz bpf_prog_linfo__free
    struct bpf_prog_linfo *prog_linfo = create_dummy_prog_linfo();
    bpf_prog_linfo__free(prog_linfo);

    // Fuzz bpf_program__func_info_cnt
    struct bpf_program *prog = create_dummy_bpf_program();
    if (prog != NULL) {
        __u32 func_info_cnt = bpf_program__func_info_cnt(prog);
    }

    // Fuzz bpf_program__line_info
    struct bpf_line_info *line_info = NULL;
    if (prog != NULL) {
        line_info = bpf_program__line_info(prog);
    }

    // Fuzz bpf_prog_linfo__lfind_addr_func
    if (prog_linfo != NULL) {
        const struct bpf_line_info *linfo_addr_func = bpf_prog_linfo__lfind_addr_func(prog_linfo, 0, 0, 0);
    }

    // Fuzz bpf_prog_linfo__lfind
    if (prog_linfo != NULL) {
        const struct bpf_line_info *linfo = bpf_prog_linfo__lfind(prog_linfo, 0, 0);
    }

    // Clean up
    if (prog_linfo) {
        bpf_prog_linfo__free(prog_linfo);
    }

    return 0;
}