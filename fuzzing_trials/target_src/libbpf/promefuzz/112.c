// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_object__open_subskeleton at libbpf.c:14395:5 in libbpf.h
// bpf_object__open_skeleton at libbpf.c:14365:5 in libbpf.h
// bpf_object__load_skeleton at libbpf.c:14465:5 in libbpf.h
// bpf_object__attach_skeleton at libbpf.c:14491:5 in libbpf.h
// libbpf_num_possible_cpus at libbpf.c:14294:5 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>
#include <elf.h>

static struct bpf_object_skeleton *create_bpf_object_skeleton(const uint8_t *Data, size_t Size) {
    struct bpf_object_skeleton *skeleton = malloc(sizeof(struct bpf_object_skeleton));
    if (!skeleton)
        return NULL;

    skeleton->sz = sizeof(struct bpf_object_skeleton);
    skeleton->name = "dummy_skeleton";
    skeleton->data = Data;
    skeleton->data_sz = Size;
    skeleton->obj = NULL;
    skeleton->map_cnt = 0;
    skeleton->map_skel_sz = sizeof(struct bpf_map_skeleton);
    skeleton->maps = NULL;
    skeleton->prog_cnt = 0;
    skeleton->prog_skel_sz = sizeof(struct bpf_prog_skeleton);
    skeleton->progs = NULL;

    return skeleton;
}

static void cleanup_bpf_object_skeleton(struct bpf_object_skeleton *skeleton) {
    if (skeleton) {
        free(skeleton);
    }
}

static struct bpf_object_open_opts *create_bpf_object_open_opts() {
    struct bpf_object_open_opts *opts = malloc(sizeof(struct bpf_object_open_opts));
    if (!opts)
        return NULL;

    opts->sz = sizeof(struct bpf_object_open_opts);
    opts->object_name = "dummy_object";
    opts->relaxed_maps = false;
    opts->pin_root_path = "/sys/fs/bpf";
    opts->kconfig = NULL;
    opts->btf_custom_path = NULL;
    opts->kernel_log_buf = NULL;
    opts->kernel_log_size = 0;
    opts->kernel_log_level = 0;
    opts->bpf_token_path = NULL;

    return opts;
}

static void cleanup_bpf_object_open_opts(struct bpf_object_open_opts *opts) {
    if (opts) {
        free(opts);
    }
}

int LLVMFuzzerTestOneInput_112(const uint8_t *Data, size_t Size) {
    struct bpf_object_skeleton *skeleton = create_bpf_object_skeleton(Data, Size);
    if (!skeleton)
        return 0;

    struct bpf_object_open_opts *opts = create_bpf_object_open_opts();
    if (!opts) {
        cleanup_bpf_object_skeleton(skeleton);
        return 0;
    }

    // Fuzz bpf_object__open_skeleton
    int ret = bpf_object__open_skeleton(skeleton, opts);
    if (ret < 0) {
        cleanup_bpf_object_open_opts(opts);
        cleanup_bpf_object_skeleton(skeleton);
        return 0;
    }

    // Fuzz bpf_object__load_skeleton
    ret = bpf_object__load_skeleton(skeleton);

    // Fuzz bpf_object__attach_skeleton
    ret = bpf_object__attach_skeleton(skeleton);

    // Fuzz libbpf_num_possible_cpus
    int ncpus = libbpf_num_possible_cpus();
    if (ncpus < 0) {
        // Handle error
    }

    // Fuzz bpf_object__open_subskeleton
    struct bpf_object_subskeleton subskeleton = {
        .sz = sizeof(struct bpf_object_subskeleton),
        .obj = NULL,
        .map_cnt = 0,
        .map_skel_sz = sizeof(struct bpf_map_skeleton),
        .maps = NULL,
        .prog_cnt = 0,
        .prog_skel_sz = sizeof(struct bpf_prog_skeleton),
        .progs = NULL,
        .var_cnt = 0,
        .var_skel_sz = sizeof(struct bpf_var_skeleton),
        .vars = NULL,
    };
    ret = bpf_object__open_subskeleton(&subskeleton);

    cleanup_bpf_object_open_opts(opts);
    cleanup_bpf_object_skeleton(skeleton);

    return 0;
}