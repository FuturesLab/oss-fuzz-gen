#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Initialize a BPF object
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0;
    }

    // Load the BPF object
    if (bpf_object__load(obj) < 0) {
        bpf_object__close(obj);
        return 0;
    }

    // Iterate over programs in the BPF object
    struct bpf_program *prog;
    bpf_object__for_each_program(prog, obj) {
        // Set log buffer for the program
        size_t buf_size = size > 0 ? size : 1;
        char *log_buf = (char *)malloc(buf_size);
        if (log_buf == NULL) {
            bpf_object__close(obj);
            return 0;
        }

        // Copy data into log_buf, ensuring it is null-terminated
        memcpy(log_buf, data, buf_size - 1);
        log_buf[buf_size - 1] = '\0';

        // Call the function under test
        bpf_program__set_log_buf(prog, log_buf, buf_size);

        // Clean up
        free(log_buf);
    }

    // Close the BPF object
    bpf_object__close(obj);

    return 0;
}