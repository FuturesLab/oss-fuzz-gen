#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "/src/libbpf/include/uapi/linux/fcntl.h"
#include "libbpf.h"

int LLVMFuzzerTestOneInput_235(const uint8_t *data, size_t size) {
    struct bpf_object *obj = NULL;
    int result;

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Load the BPF object from the temporary file
    obj = bpf_object__open(tmpl);
    if (!obj) {
        close(fd);
        return 0;
    }

    // Call the function-under-test
    result = bpf_object__load(obj);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__load to bpf_program__set_attach_target
    const char yghqgemc[1024] = "cuzeo";


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__load to perf_buffer__buffer
    const char ekrdaofs[1024] = "slito";
    struct bpf_object* ret_bpf_object__open_zjrva = bpf_object__open(ekrdaofs);
    if (ret_bpf_object__open_zjrva == NULL){
    	return 0;
    }
    int ret_bpf_object__prepare_pkptv = bpf_object__prepare(NULL);
    if (ret_bpf_object__prepare_pkptv < 0){
    	return 0;
    }

    int ret_perf_buffer__buffer_ijrnr = perf_buffer__buffer(NULL, result, (void **)&ret_bpf_object__open_zjrva, (size_t *)&ret_bpf_object__prepare_pkptv);
    if (ret_perf_buffer__buffer_ijrnr < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_bpf_program__set_attach_target_knnsb = bpf_program__set_attach_target(NULL, result, yghqgemc);
    if (ret_bpf_program__set_attach_target_knnsb < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bpf_object__close(obj);
    close(fd);
    unlink(tmpl);

    return 0;
}