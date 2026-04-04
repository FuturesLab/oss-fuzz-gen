#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "/src/libbpf/include/uapi/linux/fcntl.h"
#include "libbpf.h"

int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
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
    int ret_libbpf_unregister_prog_handler_bxwyf = libbpf_unregister_prog_handler(64);
    if (ret_libbpf_unregister_prog_handler_bxwyf < 0){
    	return 0;
    }
    int ret_bpf_object__prepare_wnptc = bpf_object__prepare(obj);
    if (ret_bpf_object__prepare_wnptc < 0){
    	return 0;
    }

    int ret_perf_buffer__buffer_spuoi = perf_buffer__buffer(NULL, ret_libbpf_unregister_prog_handler_bxwyf, (void **)&obj, (size_t *)&ret_bpf_object__prepare_wnptc);
    if (ret_perf_buffer__buffer_spuoi < 0){
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