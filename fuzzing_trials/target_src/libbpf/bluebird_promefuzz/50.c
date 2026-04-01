#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libbpf.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct bpf_object *load_bpf_object(const char *file)
{
    struct bpf_object *obj = bpf_object__open_file(file, NULL);
    if (!obj) {
        fprintf(stderr, "Failed to open BPF object file %s\n", file);
        return NULL;
    }

    if (bpf_object__load(obj)) {
        fprintf(stderr, "Failed to load BPF object\n");
        bpf_object__close(obj);
        return NULL;
    }

    return obj;
}

static void fuzz_bpf_program(const struct bpf_program *prog)
{
    const char *name = bpf_program__name(prog);
    const char *section_name = bpf_program__section_name(prog);
    __u32 line_info_cnt = bpf_program__line_info_cnt(prog);
    struct bpf_func_info *func_info = bpf_program__func_info(prog);

    if (name)
        printf("Program name: %s\n", name);
    if (section_name)
        printf("Section name: %s\n", section_name);
    printf("Line info count: %u\n", line_info_cnt);
    if (func_info)
        printf("Function info: insn_off=%u, type_id=%u\n", func_info->insn_off, func_info->type_id);
}

static void fuzz_bpf_object(struct bpf_object *obj)
{
    struct bpf_program *prog = NULL;
    while ((prog = bpf_object__next_program(obj, prog)) != NULL) {
        fuzz_bpf_program(prog);
    }
}

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size)
{
    // Create a dummy file to simulate a BPF object file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        perror("fopen");
        return 0;
    }

    if (fwrite(Data, 1, Size, file) != Size) {
        perror("fwrite");
        fclose(file);
        return 0;
    }
    fclose(file);

    struct bpf_object *obj = load_bpf_object("./dummy_file");
    if (!obj) {
        return 0;
    }

    fuzz_bpf_object(obj);

    bpf_object__close(obj);
    remove("./dummy_file");

    return 0;
}