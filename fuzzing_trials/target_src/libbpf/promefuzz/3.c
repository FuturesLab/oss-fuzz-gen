// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// libbpf_set_print at libbpf.c:267:19 in libbpf.h
// bpf_object__open_mem at libbpf.c:8413:1 in libbpf.h
// bpf_object__close at libbpf.c:9432:6 in libbpf.h
// libbpf_set_print at libbpf.c:267:19 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <libbpf.h>

// Dummy print function for libbpf_set_print
static int dummy_print_fn(enum libbpf_print_level level, const char *format, va_list args) {
    return vfprintf(stderr, format, args);
}

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    // Step 1: Set custom print function for libbpf
    libbpf_print_fn_t old_print_fn = libbpf_set_print(dummy_print_fn);

    // Step 2: Open BPF object from memory buffer
    struct bpf_object *bpf_obj = bpf_object__open_mem(Data, Size, NULL);

    // Step 3: Close BPF object if it was successfully opened
    if (bpf_obj) {
        bpf_object__close(bpf_obj);
    }

    // Restore old print function
    libbpf_set_print(old_print_fn);

    return 0;
}