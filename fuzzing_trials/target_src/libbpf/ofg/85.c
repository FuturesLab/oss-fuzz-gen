#include <stddef.h>
#include <stdint.h>
#include "/src/libbpf/src/libbpf.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    struct bpf_object *bpf_obj = bpf_object__open_mem(data, size, NULL);
    if (!bpf_obj) {
        return 0;
    }

    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        bpf_object__close(bpf_obj);
        return 0;
    }
    close(fd);

    // Call the function-under-test
    bpf_object__pin_programs(bpf_obj, tmpl);

    // Clean up
    unlink(tmpl);
    bpf_object__close(bpf_obj);

    return 0;
}